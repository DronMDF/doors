// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BytesOk.h"
#include <stdexcept>
#include <protocol.h>

using namespace std;

BytesOk::BytesOk(const vector<uint8_t> &bytes)
	: bytes(bytes)
{
	if (bytes.size() < sizeof(Ok)) {
		throw runtime_error("Wrong OK size");
	}

	const Ok *reply = reinterpret_cast<const Ok *>(&bytes[0]);
	if (be32toh(reply->version) != VERSION) {
		throw runtime_error("Wrong protocol version");
	}

	if (be32toh(reply->command) != OK) {
		throw runtime_error("Wrong OK command");
	}
}

BytesOk::BytesOk(const void *ptr, size_t size)
	: BytesOk(
		vector<uint8_t>(
			static_cast<const uint8_t *>(ptr),
			static_cast<const uint8_t *>(ptr) + size
		)
	  )
{
}

uint32_t BytesOk::opt() const
{
	const Ok *reply = reinterpret_cast<const Ok *>(&bytes[0]);
	return be32toh(reply->opt);
}
