// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ActionRepr.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <arpa/inet.h>
#include <core/RawBytes.h>
#include "TestSocket.h"

using namespace std;

ActionRepr::ActionRepr(const shared_ptr<const Action> &action, const vector<uint32_t> &request)
	: action(action), request(request)
{
}

string ActionRepr::asString() const
{
	// htonl all
	vector<uint32_t> rw;
	transform(request.begin(), request.end(), back_inserter(rw), htonl);
	vector<uint8_t> rb(rw.size() * sizeof(uint32_t));
	memcpy(&rb[0], &rw[0], rb.size());

	vector<uint8_t> reply;
	action->process(
		make_shared<RawBytes>(&rw[0], rw.size() * sizeof(uint32_t)),
		make_shared<TestSocket>(&reply)
	);

	ostringstream out;
	for (int i = 0; i < reply.size(); i++) {
		out << hex << setw(2) << setfill('0') << unsigned(reply[i]);
		if (i % 4 == 3) {
			out << " ";
		}
	}

	return out.str();
}
