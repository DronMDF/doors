// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <string>
#include "Storage.h"

class HttpService {
public:
	virtual ~HttpService() = default;

	virtual void request(
		const std::string &uri,
		const std::string &request,
		// @todo #95 StorageHandler не самый подходящий обработчик для HttpService,
		//  Должен быть HttpHandler
		const std::shared_ptr<const StorageHandler> &handler
	) const = 0;
};
