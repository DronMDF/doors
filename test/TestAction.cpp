// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "TestAction.h"
#include <cstring>
#include <core/Socket.h>

using namespace std;

TestAction::TestAction(const vector<uint32_t> &reply)
	: reply(reply)
{
}

bool TestAction::process(
	const shared_ptr<const Bytes> &request,
	const shared_ptr<Socket> &socket
) const
{
	vector<uint32_t> berep;
	for (const auto &v : reply) {
		berep.push_back(htobe32(v));
	}
	vector<uint8_t> rv(berep.size() * sizeof(uint32_t));
	memcpy(&rv[0], &berep[0], rv.size());
	socket->send(rv);
	return true;
}
