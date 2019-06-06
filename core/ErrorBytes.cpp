// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ErrorBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

ErrorBytes::ErrorBytes(const uint32_t id)
	: id(id)
{
}

vector<uint8_t> ErrorBytes::raw() const
{
	Error reply;
	reply.id = htobe32(id);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
