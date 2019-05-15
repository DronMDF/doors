// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "NetIoService.h"
#include <functional>
#include <iostream>
#include <regex>
#include <asio/streambuf.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/socket.hpp>
#include "RawBytes.h"
#include "Storage.h"
#include "UdpHandler.h"

using namespace std;
using asio::ip::udp;
using asio::ip::tcp;

class UdpAsyncRequest final : public enable_shared_from_this<UdpAsyncRequest> {
public:
	UdpAsyncRequest(
		const shared_ptr<udp::socket> &socket,
		const udp::endpoint &endpoint,
		const vector<uint8_t> &request,
		const shared_ptr<const UdpHandler> &handler
	) : socket(socket), endpoint(endpoint), request(request), handler(handler), reply(1024)
	{
	}

	void start() {
		socket->async_send_to(
			asio::buffer(request),
			endpoint,
			bind(
				&UdpAsyncRequest::handle_send,
				shared_from_this(),
				placeholders::_1,
				placeholders::_2
			)
		);
	}

	void handle_send(error_code ec, size_t size [[gnu::unused]]) {
		if (!ec) {
			// @todo #71 endpoint в данном контексте определяется при приходе пакета
			//  Но мы работаем с конкретным, и не должны принимать пакеты от других.
			//  Это можно интерпретировать как ошибку
			socket->async_receive_from(
				asio::buffer(reply),
				endpoint,
				bind(
					&UdpAsyncRequest::handle_recv,
					shared_from_this(),
					placeholders::_1,
					placeholders::_2
				)
			);
		} else {
			cout << "UDP send error" << endl;
		}
	}

	void handle_recv(error_code ec, size_t size) const {
		if (!ec) {
			handler->handle(make_shared<RawBytes>(&reply[0], size));
		} else {
			cout << "UDP recv error" << endl;
		}
	}

private:
	const shared_ptr<udp::socket> socket;
	udp::endpoint endpoint;
	const vector<uint8_t> request;
	const shared_ptr<const UdpHandler> handler;
	vector<uint8_t> reply;
};

class HttpAsyncRequest final : public enable_shared_from_this<HttpAsyncRequest> {
public:
	HttpAsyncRequest(
		asio::io_context *context,
		const string &request,
		const shared_ptr<const StorageHandler> &handler
	) : socket(*context), request(request), handler(handler)
	{
	}

	void start(const tcp::resolver::results_type &endpoints)
	{
		asio::async_connect(
			socket,
			endpoints,
			bind(
				&HttpAsyncRequest::handle_connect,
				shared_from_this(),
				placeholders::_1
			)
		);
	}

	void handle_connect(const error_code &error)
	{
		if (error) {
			throw runtime_error("Unable to connect HttpAsyncConnect");
		}

		asio::async_write(
			socket,
			asio::buffer(request),
			bind(
				&HttpAsyncRequest::handle_write,
				shared_from_this(),
				placeholders::_1
			)
		);
	}

	void handle_write(const error_code &error)
	{
		if (error) {
			throw runtime_error("Unable to write data in HttpAsyncConnect");
		}

		asio::async_read_until(
			socket,
			reply,
			"\r\n\r\n",
			bind(
				&HttpAsyncRequest::handle_header,
				shared_from_this(),
				placeholders::_1,
				placeholders::_2
			)
		);
	}

	void handle_header(const error_code &error, size_t bytes)
	{
		if (error) {
			throw runtime_error("Unable to read header in HttpAsyncConnect");
		}
		const string hdr(
			asio::buffers_begin(reply.data()),
			asio::buffers_begin(reply.data()) + bytes
		);
		reply.consume(bytes);

		smatch m;
		if (!regex_search(hdr, m, regex(R"(Content-Length: (\d+))"))) {
			throw runtime_error("Wrong response header in HttpAsyncRequestStorage");
		}

		const size_t body_size = stoi(m[1]);

		if (reply.size() >= body_size) {
			handle_body({}, body_size);
		} else {
			asio::async_read(
				socket,
				reply,
				asio::transfer_at_least(body_size),
				bind(
					&HttpAsyncRequest::handle_body,
					shared_from_this(),
					placeholders::_1,
					placeholders::_2
				)
			);
		}
	}

	void handle_body(const error_code &error, size_t bytes)
	{
		if (error) {
			throw runtime_error("Unable to read header in HttpAsyncConnect");
		}

		const string body(
			asio::buffers_begin(reply.data()),
			asio::buffers_begin(reply.data()) + bytes
		);

		handler->handle(nlohmann::json::parse(body));
	}

private:
	tcp::socket socket;
	const string request;
	const shared_ptr<const StorageHandler> handler;
	asio::streambuf reply;
};

NetIoService::NetIoService(asio::io_context *context)
	: context(context)
{
}

void NetIoService::async_udp_request(
	const string &address,
	in_port_t port,
	const shared_ptr<const Bytes> &request,
	const shared_ptr<const UdpHandler> &handler
) const
{
	auto socket = make_shared<udp::socket>(
		ref(*context),
		udp::endpoint(udp::v4(), 0)
	);

	// @todo #66 Необходимо использовать асинхронное определение
	udp::resolver resolver(*context);
	const auto endpoint = *resolver.resolve(udp::v4(), address, to_string(port)).begin();

	make_shared<UdpAsyncRequest>(socket, endpoint, request->raw(), handler)->start();
}

void NetIoService::async_http_request(
	const string &uri,
	const string &request,
	const shared_ptr<const StorageHandler> &handler
) const
{
	smatch m;
	// @todo #66 copy-paste from HttpStorage
	if (!regex_match(uri, m, regex(R"(http://([\w\.]+):(\d+))"))) {
		throw runtime_error("Wrong uri in NetIoService");
	}

	tcp::socket s(*context);
	tcp::resolver resolver(*context);
	const auto endpoints = resolver.resolve(string(m[1]), string(m[2]));

	make_shared<HttpAsyncRequest>(context, request, handler)->start(endpoints);
}
