// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "SaboteurStorage.h"

using namespace std;

nlohmann::json SaboteurStorage::query(const string &query) const
{
	throw runtime_error("Not found");
}

void SaboteurStorage::update(const string &query, const nlohmann::json &data)
{
	throw runtime_error("Not access");
}

