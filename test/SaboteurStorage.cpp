// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "SaboteurStorage.h"

using namespace std;

class SaboteurStorageResponse final : public StorageResponse {
public:
	nlohmann::json json() const override
	{
		throw runtime_error("Sabotage");
	}
};

void SaboteurStorage::query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	handler->handle(make_shared<SaboteurStorageResponse>());
}

void SaboteurStorage::update(const string &query, const nlohmann::json &data)
{
	throw runtime_error("Not access");
}

