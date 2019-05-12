// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LogStorage.h"

using namespace std;

void LogStorage::async_query(
	const string &query [[gnu::unused]],
	const shared_ptr<const StorageHandler> &handler [[gnu::unused]]
) const
{
	throw runtime_error("No log query");
}

void LogStorage::update(
	const string &query,
	const nlohmann::json &data [[gnu::unused]]
)
{
	updates += query + "\n";
}

string LogStorage::asString()
{
	return updates;
}
