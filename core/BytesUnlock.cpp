// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BytesUnlock.h"
#include <stdexcept>
#include <protocol.h>

using namespace std;

BytesUnlock::BytesUnlock(const vector<uint8_t> &bytes)
	: bytes(bytes)
{
	if (bytes.size() < sizeof(Unlock)) {
		throw runtime_error("Wrong UNLOCK header");
	}

	const Unlock *reply = reinterpret_cast<const Unlock *>(&bytes[0]);
	if (be32toh(reply->version) != VERSION) {
		throw runtime_error("Wrong protocol version");
	}

	if (be32toh(reply->command) != UNLOCK) {
		throw runtime_error("Wrong UNLOCK command");
	}
}

uint32_t BytesUnlock::id() const
{
	const auto *reply = reinterpret_cast<const Unlock *>(&bytes[0]);
	return be32toh(reply->id);
}

uint32_t BytesUnlock::lock_id() const
{
	const auto *reply = reinterpret_cast<const Unlock *>(&bytes[0]);
	return be32toh(reply->lock_no);
}

uint64_t BytesUnlock::key_id() const
{
	const auto *reply = reinterpret_cast<const Unlock *>(&bytes[0]);
	return be64toh(reply->key);
}
