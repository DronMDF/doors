// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "IoService.h"
#include "Storage.h"

class HttpStorage final : public Storage {
public:
	HttpStorage(const std::string &uri, const std::shared_ptr<IoService> &service);

	void query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;
	void update(const std::string &query, const nlohmann::json &data) override;
private:
	const std::string uri;
	const std::shared_ptr<IoService> service;
};
