// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "NullStorage.h"

using namespace std;

nlohmann::json NullStorage::query(const string &query [[gnu::unused]]) const
{
	throw runtime_error("No result");
}

void NullStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
}
