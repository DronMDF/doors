// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "KeyStatusBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

KeyStatusBytes::KeyStatusBytes(
	uint32_t id,
	uint64_t key,
	uint64_t contract,
	uint32_t expired,
	int32_t money
) : id(id), key(key), contract(contract), expired(expired), money(money)
{
}

vector<uint8_t> KeyStatusBytes::raw() const
{
	KeyStatus reply;
	reply.id = htobe32(id);
	reply.key = htobe64(key);
	reply.contract = htobe64(contract);
	reply.expired = htobe32(expired);
	reply.money = htobe32(money);

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	return rv;
}
