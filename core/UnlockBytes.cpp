// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "UnlockBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

UnlockBytes::UnlockBytes(uint32_t id, uint32_t lock_no, uint64_t key)
	: id(id), lock_no(lock_no), key(key)
{
}

vector<uint8_t> UnlockBytes::raw() const
{
	Unlock reply;
	reply.id = htobe32(id);
	reply.lock_no = htobe32(lock_no);
	reply.key = htobe64(key);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
