// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryTask.h"
#include <asio/ts/internet.hpp>
#include <fmt/format.h>
#include "BytesInventory.h"
#include "IoService.h"
#include "InventoryReqBytes.h"
#include "Storage.h"
#include "UdpHandler.h"

using namespace std;
using asio::ip::udp;

class InventoryReplyHandler final : public UdpHandler
{
public:
	InventoryReplyHandler(
		const string &address,
		in_port_t port,
		const shared_ptr<Storage> &storage
	) : address(address), port(port), storage(storage)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		BytesInventory inventory(reply);
		storage->update(
			fmt::format("/controller/{0}:{1}/locks", address, port),
			nlohmann::json::object({{"locks", inventory.locks()}})
		);
	}
private:
	const string address;
	in_port_t port;
	const shared_ptr<Storage> storage;
};

InventoryTask::InventoryTask(
	const string &address,
	in_port_t port,
	const shared_ptr<Storage> &storage,
	const shared_ptr<IoService> &service
) : address(address), port(port), storage(storage), service(service)
{
}

void InventoryTask::run() const
{
	service->async_udp_request(
		address,
		port,
		make_shared<InventoryReqBytes>(),
		make_shared<InventoryReplyHandler>(address, port, storage)
	);
}
