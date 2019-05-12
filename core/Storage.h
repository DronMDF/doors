// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <nlohmann/json.hpp>

class StorageHandler {
public:
	virtual ~StorageHandler() = default;
	// @todo #85 Должен ли handler принимать еще код ошибки?
	//  Что делать, если storage не в состоянии предоставить результат?
	virtual void handle(const nlohmann::json &data) const = 0;
};

class Storage {
public:
	virtual ~Storage() = default;

	virtual void async_query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const = 0;

	virtual void update(const std::string &query, const nlohmann::json &data) = 0;
};
