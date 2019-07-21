// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "RawBytes.h"

using namespace std;

RawBytes::RawBytes(const vector<uint8_t> &bytes)
	: bytes(bytes)
{
}

RawBytes::RawBytes(const void *ptr, size_t size)
	: RawBytes(
		vector<uint8_t>(
			static_cast<const uint8_t *>(ptr),
			static_cast<const uint8_t *>(ptr) + size
		)
	)
{
}

vector<uint8_t> RawBytes::raw() const
{
	return bytes;
}
