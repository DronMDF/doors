// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <core/Storage.h>

class LogStorage final : public Storage {
public:
	void query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;

	void update(const std::string &query, const nlohmann::json &data) override;

	std::string asString();
private:
	std::string updates;
};
