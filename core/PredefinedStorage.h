// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Storage.h"

class PredefinedStorage final : public Storage {
public:
	// Primary
	explicit PredefinedStorage(const std::map<std::string, nlohmann::json> &info);
	// Secondary
	PredefinedStorage(const std::string &query, const nlohmann::json &result);

	void query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;

	void update(const std::string &query, const nlohmann::json &data) override;
private:
	const std::map<std::string, nlohmann::json> info;
};
