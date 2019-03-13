// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusAction.h"
#include <cstring>
#include <protocol.h>
#include "Socket.h"

using namespace std;

bool StatusAction::process(
	const vector<uint8_t> &request,
	const shared_ptr<Socket> &socket
) const
{
	if (request.size() < sizeof(KeyStatusRequest)) {
		return false;
	}

	const auto *req = reinterpret_cast<const KeyStatusRequest *>(&request[0]);
	if (ntohl(req->command) != C2S_KEY_STATUS) {
		return false;
	}

	KeyStatusReply reply;
	reply.key = req->key;
	// @todo #21 Необходимо по номеру ключа достать всю необходимую информацию из БД,
	//  или из кеша.

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	socket->send(rv);

	return true;
}
