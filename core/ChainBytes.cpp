// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ChainBytes.h"

using namespace std;

ChainBytes::ChainBytes(const shared_ptr<const Bytes> &a, const shared_ptr<const Bytes> &b)
	: a(a), b(b)
{
}

vector<uint8_t> ChainBytes::raw() const
{
	auto r = a->raw();
	const auto bb = b->raw();
	r.insert(r.end(), bb.begin(), bb.end());
	return r;
}
