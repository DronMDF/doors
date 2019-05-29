// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <nlohmann/json.hpp>

class StorageResponse {
public:
	virtual ~StorageResponse() = default;
	virtual nlohmann::json json() const = 0;
};

class StorageHandler {
public:
	virtual ~StorageHandler() = default;
	virtual void handle(const std::shared_ptr<const StorageResponse> &response) const = 0;
};

class Storage {
public:
	virtual ~Storage() = default;

	virtual void query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const = 0;

	// @todo #87 Storage::update должен принимать на вход callback
	//  Через коллбек можно делать ретрансмиты или рапортовать об ошибках.
	virtual void update(const std::string &query, const nlohmann::json &data) = 0;
};
