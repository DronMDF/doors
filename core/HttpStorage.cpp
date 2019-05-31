// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "HttpStorage.h"
#include <regex>
#include <fmt/format.h>

using namespace std;

class HttpStorageResponse final : public StorageResponse {
public:
	explicit HttpStorageResponse(const shared_ptr<const HttpResponse> &response)
		: response(response)
	{
	}

	nlohmann::json json() const override
	{
		return response->json();
	}
private:
	const shared_ptr<const HttpResponse> response;
};

class HttpStorageHandler final : public HttpHandler {
public:
	explicit HttpStorageHandler(const shared_ptr<const StorageHandler> &handler)
		: handler(handler)
	{
	}

	void handle(const shared_ptr<const HttpResponse> &response) const override
	{
		handler->handle(make_shared<HttpStorageResponse>(response));
	}
private:
	const shared_ptr<const StorageHandler> handler;
};

class NullStorageHandler final : public StorageHandler {
public:
	void handle(
		const shared_ptr<const StorageResponse> &response [[gnu::unused]]
	) const override
	{
	}
};

HttpStorage::HttpStorage(const string &uri, const shared_ptr<HttpService> &service)
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

	service->request(uri, request, make_shared<HttpStorageHandler>(handler));
}

void HttpStorage::update(const string &query, const nlohmann::json &data)
{
	const string dump = data.dump();
	const string request = fmt::format(
		"POST {0} HTTP/1.1\r\n"
		"Content-Type: text/json\r\n"
		"Content-Length: {1}\r\n"
		"\r\n"
		"{2}",
		query,
		dump.size(),
		dump
	);

	service->request(
		uri,
		request,
		make_shared<HttpStorageHandler>(make_shared<NullStorageHandler>())
	);
}
