// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryAction.h"
#include <cstring>
#include <protocol.h>
#include "Socket.h"

using namespace std;

InventoryAction::InventoryAction(const shared_ptr<Storage> &storage)
	: storage(storage)
{
}

bool InventoryAction::process(
	const vector<uint8_t> &request,
	const shared_ptr<Socket> &socket
) const
{
	if (request.size() < sizeof(uint32_t) * 2) {
		throw runtime_error("Invalid request");
	}

	const auto *req = reinterpret_cast<const InventoryReq *>(&request[0]);
	if (ntohl(req->version) != VERSION) {
		throw runtime_error("Invalid request version");
	}

	if (ntohl(req->command) == INVENTORY_REQ) {
		Inventory reply;
		// @todo #13 Наполнить ответ содержимым
		//  и содержимое должно соответствоать настройкам эмулятора.

		vector<uint8_t> rv(sizeof(reply));
		memcpy(&rv[0], &reply, sizeof(reply));
		socket->send(rv);
		return true;
	}

	throw runtime_error("Unknown request command");
}
