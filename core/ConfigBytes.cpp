// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ConfigBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

ConfigBytes::ConfigBytes(uint32_t id, uint32_t lock_no, uint32_t timeout, uint32_t ntry)
	: id(id), lock_no(lock_no), timeout(timeout), ntry(ntry)
{
}

vector<uint8_t> ConfigBytes::raw() const
{
	Config reply;
	reply.id = htobe32(id);
	reply.lock_no = htobe32(lock_no);
	reply.timeout = htobe32(timeout);
	reply.ntry = htobe32(ntry);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
