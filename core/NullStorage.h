// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Storage.h"

class NullStorage final : public Storage {
public:
	nlohmann::json query(const std::string &query) const override;
	void update(const std::string &query, const nlohmann::json &data) override;
};