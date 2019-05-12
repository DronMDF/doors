// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryAction.h"
#include <cstring>
#include <endian.h>
#include <protocol.h>
#include "ChainBytes.h"
#include "DefaultStorage.h"
#include "InventoryBytes.h"
#include "List32Bytes.h"
#include "Socket.h"

using namespace std;

class InventoryStorageHandler final : public StorageHandler {
public:
	InventoryStorageHandler(const InventoryReq &req, const shared_ptr<Socket> &socket)
		: req(req), socket(socket)
	{
	}

	void handle(const nlohmann::json &data) const override
	{
		const auto locks = data["locks"];

		ChainBytes reply(
			make_shared<InventoryBytes>(be32toh(req.id)),
			make_shared<List32Bytes>(vector<uint32_t>(locks.begin(), locks.end()))
		);

		socket->send(reply.raw());
	}
private:
	const InventoryReq req;
	const shared_ptr<Socket> socket;
};

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

	DefaultStorage(
		storage,
		R"({ "locks": [] })"_json
	).async_query("/locks", make_shared<InventoryStorageHandler>(*req, socket));
	// @todo #85 InventoryAction возвращает результат асинхронно.
	//  Мы все делаем асинхронно.
	return true;
}
