// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <string>
#include "Storage.h"

class HttpHandler {
public:
	virtual ~HttpHandler() = default;
	// @todo #143 В качестве аргумента handle Должен принимать HttpResponse
	//  Который на другом уровне логики парсится так, как надо.
	//  И может инкапсулировать в себя ошибку
	virtual void handle(const nlohmann::json &data) const = 0;
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
