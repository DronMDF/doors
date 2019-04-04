// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "List32Bytes.h"
#include <cstring>
#include <endian.h>

using namespace std;

List32Bytes::List32Bytes(const vector<uint32_t> &values)
	: values(values)
{
}

vector<uint8_t> List32Bytes::raw() const
{
	vector<uint32_t> be;
	for (const auto &l : values) {
		be.push_back(htobe32(l));
	}

	vector<uint8_t> rv(sizeof(uint32_t) + be.size() * sizeof(uint32_t));
	const uint32_t be_size = htobe32(be.size());
	memcpy(&rv[0], &be_size, sizeof(be_size));
	memcpy(&rv[sizeof(uint32_t)], &be[0], be.size() * sizeof(uint32_t));
	return rv;
}
