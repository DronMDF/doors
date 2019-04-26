// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <nlohmann/json.hpp>

class StorageHandler {
public:
	virtual ~StorageHandler() = default;
	virtual void handle(const nlohmann::json &data) const = 0;
};

class Storage {
public:
	virtual ~Storage() = default;

	// @todo #66 Нужно убить синхронное API в Storage
	virtual nlohmann::json query(const std::string &query) const = 0;
	virtual void async_query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const = 0;

	virtual void update(const std::string &query, const nlohmann::json &data) = 0;
};
