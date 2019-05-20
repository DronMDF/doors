// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BytesLock.h"
#include <stdexcept>
#include <protocol.h>

using namespace std;

BytesLock::BytesLock(const vector<uint8_t> &bytes)
	: bytes(bytes)
{
	if (bytes.size() < sizeof(Lock)) {
		throw runtime_error("Wrong LOCK header");
	}

	const Lock *reply = reinterpret_cast<const Lock *>(&bytes[0]);
	if (be32toh(reply->version) != VERSION) {
		throw runtime_error("Wrong protocol version");
	}

	if (be32toh(reply->command) != LOCK) {
		throw runtime_error("Wrong LOCK command");
	}
}

uint32_t BytesLock::id() const
{
	const Lock *reply = reinterpret_cast<const Lock *>(&bytes[0]);
	return be32toh(reply->id);
}
