// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "NullStorage.h"

using namespace std;

class NullStorageResponse final : public StorageResponse {
public:
	nlohmann::json json() const override
	{
		return {};
	}
};

void NullStorage::query(
	const string &query [[gnu::unused]],
	const shared_ptr<const StorageHandler> &handler
) const
{
	handler->handle(make_shared<NullStorageResponse>());
}

void NullStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
}
