// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryAction.h"
#include <cstring>
#include <endian.h>
#include <protocol.h>
#include "Socket.h"
#include "Storage.h"

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
	if (be32toh(req->version) != VERSION) {
		throw runtime_error("Invalid request version");
	}

	if (be32toh(req->command) != INVENTORY_REQ) {
		throw runtime_error("Unknown request command");
	}

	// @todo #18 Необходим объект типа InventoryReply,
	//  который будет формироваться из request'а и дополняться списком замков.
	//  Из всего этого добра будет сформирован байтовый массив asBytes()

	const auto locks = storage->query("/locks");
	vector<uint32_t> rl;
	for (const auto &l : locks.value("locks", nlohmann::json::array())) {
		rl.push_back(htobe32(l));
	}

	Inventory reply;
	reply.id = req->id;		// be32
	reply.lock_count = htobe32(rl.size());
	vector<uint8_t> rv(sizeof(reply) + sizeof(uint32_t) * rl.size());
	memcpy(&rv[0], &reply, sizeof(reply));
	memcpy(&rv[sizeof(reply)], &rl[0], sizeof(uint32_t) * rl.size());

	socket->send(rv);

	return true;
}
