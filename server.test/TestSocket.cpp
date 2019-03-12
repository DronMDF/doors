// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "TestSocket.h"

using namespace std;

TestSocket::TestSocket(vector<uint8_t> * const packet)
	: packet(packet)
{
}

void TestSocket::send(const vector<uint8_t> &p) const
{
	packet->assign(p.begin(), p.end());
}
