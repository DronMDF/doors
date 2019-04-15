// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <nlohmann/json.hpp>

class Storage {
public:
	virtual ~Storage() = default;

	// @todo #64 Асинхронные запросы должны иметь другой API, с коллбеками
	virtual nlohmann::json query(const std::string &query) const = 0;
	virtual void update(const std::string &query, const nlohmann::json &data) = 0;
};
