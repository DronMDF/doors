// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "TestStorage.h"

using namespace std;

TestStorage::TestStorage(const map<string, nlohmann::json> &info)
	: info(info)
{
}

TestStorage::TestStorage(const string &query, const nlohmann::json &result)
	: TestStorage({make_pair(query, result)})
{
}

void TestStorage::query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	handler->handle(info.at(query));
}

void TestStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
}
