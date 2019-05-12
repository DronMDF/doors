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

void HttpStorage::query(
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
