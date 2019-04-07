// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "IdentBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

IdentBytes::IdentBytes(uint32_t id, uint32_t lock_no)
	: id(id), lock_no(lock_no)
{
}

vector<uint8_t> IdentBytes::raw() const
{
	Ident reply;
	reply.id = htobe32(id);
	reply.lock_no = htobe32(lock_no);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
