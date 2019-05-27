// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <string>
#include "Storage.h"

class HttpResponse {
public:
	virtual ~HttpResponse() = default;
	virtual nlohmann::json json() const = 0;
};

class HttpHandler {
public:
	virtual ~HttpHandler() = default;
	virtual void handle(const std::shared_ptr<const HttpResponse> &response) const = 0;
};

class HttpService {
public:
	virtual ~HttpService() = default;

	virtual void request(
		const std::string &uri,
		const std::string &request,
		const std::shared_ptr<const HttpHandler> &handler
	) const = 0;
};
