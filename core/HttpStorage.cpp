// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "HttpStorage.h"
#include <regex>
#include <asio.hpp>
#include <fmt/format.h>

using namespace std;
using asio::ip::tcp;

HttpStorage::HttpStorage(const string &uri, const shared_ptr<IoService> &service)
	: uri(uri), service(service)
{
}

nlohmann::json HttpStorage::query(const string &query) const
{
	smatch m;
	// @todo #66 Пока поддерживается только форма http с указанием порта
	if (!regex_match(uri, m, regex(R"(http://(\w+):(\d+))"))) {
		throw runtime_error("Wrong uri in HttpStorage");
	}

	asio::io_context io_context;

	tcp::socket s(io_context);
	tcp::resolver resolver(io_context);
	asio::connect(s, resolver.resolve(string(m[1]), string(m[2])));

	const string http_request = fmt::format(
		"GET {0} HTTP/1.1\r\n"
		"\r\n",
		query
	);
	asio::write(s, asio::buffer(http_request));

	asio::streambuf buffer;
	const size_t hdr_size = asio::read_until(s, buffer, "\r\n\r\n");
	const string hdr(
		asio::buffers_begin(buffer.data()),
		asio::buffers_begin(buffer.data()) + hdr_size
	);
	buffer.consume(hdr_size);

	smatch mh;
	if (!regex_match(hdr, mh, regex(R"(Content-Length: (\d+))"))) {
		throw runtime_error("Wrong response header in HttpStorage");
	}
	const size_t body_size = asio::read(s, buffer, asio::transfer_at_least(stoi(mh[0])));
	const string body(
		asio::buffers_begin(buffer.data()),
		asio::buffers_begin(buffer.data()) + body_size
	);

	return nlohmann::json::parse(body);
}

void HttpStorage::async_query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	const string request = fmt::format(
		"GET {0} HTTP/1.1\r\n"
		"\r\n",
		query
	);

	service->async_http_request(uri, request, handler);
}

void HttpStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
	// @todo #66 Обновление данных через HttpStorage
}
