// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "OkBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

OkBytes::OkBytes(const uint32_t id, const uint32_t opt)
	: id(id), opt(opt)
{
}

vector<uint8_t> OkBytes::raw() const
{
	Ok reply;
	reply.id = htobe32(id);
	reply.opt = htobe32(opt);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
