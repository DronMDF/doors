// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BytesInventory.h"
#include <stdexcept>
#include <protocol.h>
#include "Bytes.h"

using namespace std;

BytesInventory::BytesInventory(const vector<uint8_t> &bytes)
	: bytes(bytes)
{
	if (bytes.size() < sizeof(Inventory) + sizeof(uint32_t)) {
		throw runtime_error("Wrong Init reply");
	}

	const Inventory *reply = reinterpret_cast<const Inventory *>(&bytes[0]);
	if (be32toh(reply->version) != VERSION) {
		throw runtime_error("Wrong protool version");
	}

	if (be32toh(reply->command) != INVENTORY) {
		throw runtime_error("Wrong Init reply command");
	}
	const size_t locks_count = be32toh(
		*reinterpret_cast<const uint32_t *>(&bytes[sizeof(Inventory)])
	);
	if (bytes.size() < sizeof(Inventory) + (1 + locks_count) * sizeof(uint32_t)) {
		throw runtime_error("Wrong Init reply");
	}
}

BytesInventory::BytesInventory(const shared_ptr<const Bytes> &bytes)
	: BytesInventory(bytes->raw())
{
}

BytesInventory::BytesInventory(const void *ptr, size_t size)
	: BytesInventory(
		vector<uint8_t>(
			static_cast<const uint8_t *>(ptr),
			static_cast<const uint8_t *>(ptr) + size
		)
	  )
{
}

vector<uint32_t> BytesInventory::locks() const
{
	const uint32_t *tail = reinterpret_cast<const uint32_t *>(&bytes[sizeof(Inventory)]);
	vector<uint32_t> locks;
	for (const auto &l : vector<uint32_t>(tail + 1, tail + 1 + be32toh(*tail))) {
		locks.push_back(be32toh(l));
	}
	return locks;
}
