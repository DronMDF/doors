// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BytesRepr.h"
#include <iomanip>
#include <sstream>
#include <core/Bytes.h>

using namespace std;

BytesRepr::BytesRepr(const shared_ptr<const Bytes> &bytes)
	: bytes(bytes)
{
}

string BytesRepr::asString() const
{
	const auto raw = bytes->raw();
	ostringstream out;
	for (int i = 0; i < raw.size(); i++) {
		out << hex << setw(2) << setfill('0') << unsigned(raw[i]);
		if (i % 4 == 3) {
			out << " ";
		}
	}
	return out.str();
}
