// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "PredefinedStorage.h"

using namespace std;

PredefinedStorage::PredefinedStorage(const map<string, nlohmann::json> &info)
	: info(info)
{
}

PredefinedStorage::PredefinedStorage(const string &query, const nlohmann::json &result)
	: PredefinedStorage({make_pair(query, result)})
{
}

void PredefinedStorage::query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	handler->handle(info.at(query));
}

void PredefinedStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
}
