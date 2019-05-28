// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "AsioHttpService.h"
#include <regex>
#include <asio/streambuf.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/socket.hpp>

using namespace std;
using asio::ip::tcp;

class AsioHttpResponse final : public HttpResponse {
public:
	explicit AsioHttpResponse(const string &body)
		: body(body)
	{
	}

	nlohmann::json json() const override
	{
		return nlohmann::json::parse(body);
	}
private:
	const string body;
};

class AsioHttpError final : public HttpResponse {
public:
	AsioHttpError(const error_code &error, const string &message)
		: error(error), message(message)
	{
	}

	explicit AsioHttpError(const string &message)
		: AsioHttpError({}, message)
	{
	}

	nlohmann::json json() const override
	{
		throw system_error(error, message);
	}

private:
	const error_code error;
	const string message;
};

class AsioHttpRequest final : public enable_shared_from_this<AsioHttpRequest> {
public:
	AsioHttpRequest(
		asio::io_context *context,
		const string &request,
		const shared_ptr<const HttpHandler> &handler
	) : socket(*context), request(request), handler(handler)
	{
	}

	void start(const tcp::resolver::results_type &endpoints)
	{
		asio::async_connect(
			socket,
			endpoints,
			bind(
				&AsioHttpRequest::handle_connect,
				shared_from_this(),
				placeholders::_1
			)
		);
	}

	void handle_connect(const error_code &error)
	{
		if (error) {
			handler->handle(make_shared<AsioHttpError>(error, "Http connect failed"));
		} else {
			asio::async_write(
				socket,
				asio::buffer(request),
				bind(
					&AsioHttpRequest::handle_write,
					shared_from_this(),
					placeholders::_1
				)
			);
		}
	}

	void handle_write(const error_code &error)
	{
		if (error) {
			handler->handle(make_shared<AsioHttpError>(error, "Http write failed"));
		} else {
			asio::async_read_until(
				socket,
				reply,
				"\r\n\r\n",
				bind(
					&AsioHttpRequest::handle_header,
					shared_from_this(),
					placeholders::_1,
					placeholders::_2
				)
			);
		}
	}

	void handle_header(const error_code &error, size_t bytes)
	{
		if (error) {
			handler->handle(
				make_shared<AsioHttpError>(error, "Http read header failed")
			);
		} else {
			const string hdr(
				asio::buffers_begin(reply.data()),
				asio::buffers_begin(reply.data()) + bytes
			);
			reply.consume(bytes);

			smatch m;
			if (regex_search(hdr, m, regex(R"(Content-Length: (\d+))"))) {
				const size_t body_size = stoi(m[1]);

				if (reply.size() >= body_size) {
					handle_body({}, body_size);
				} else {
					asio::async_read(
						socket,
						reply,
						asio::transfer_at_least(body_size),
						bind(
							&AsioHttpRequest::handle_body,
							shared_from_this(),
							placeholders::_1,
							placeholders::_2
						)
					);
				}
			} else {
				handler->handle(make_shared<AsioHttpError>("Wrong Http header"));
			}
		}
	}

	void handle_body(const error_code &error, size_t bytes)
	{
		if (error) {
			handler->handle(make_shared<AsioHttpError>(error, "Http read body failed"));
		} else {
			const string body(
				asio::buffers_begin(reply.data()),
				asio::buffers_begin(reply.data()) + bytes
			);

			handler->handle(make_shared<AsioHttpResponse>(body));
		}
	}

private:
	tcp::socket socket;
	const string request;
	const shared_ptr<const HttpHandler> handler;
	asio::streambuf reply;
};


AsioHttpService::AsioHttpService(asio::io_context *context)
	: context(context)
{
}

void AsioHttpService::request(
	const string &uri,
	const string &request,
	const shared_ptr<const HttpHandler> &handler
) const
{
	smatch m;
	if (!regex_match(uri, m, regex(R"(http://([\w\.]+):(\d+))"))) {
		throw runtime_error("Wrong uri in NetIoService");
	}

	tcp::socket s(*context);
	tcp::resolver resolver(*context);
	const auto endpoints = resolver.resolve(string(m[1]), string(m[2]));

	make_shared<AsioHttpRequest>(context, request, handler)->start(endpoints);
}