// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <server.core/Storage.h>

class TestStorage final : public Storage {
public:
	// Primary
	explicit TestStorage(const std::map<std::string, nlohmann::json> &info);
	// Secondary
	TestStorage(const std::string &query, const nlohmann::json &result);

	nlohmann::json query(const std::string &query) const override;
	void update(const std::string &query, const nlohmann::json &data) override;
private:
	const std::map<std::string, nlohmann::json> info;
};
