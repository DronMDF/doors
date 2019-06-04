// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryTask.h"
#include <asio/ts/internet.hpp>
#include <fmt/format.h>
#include "BytesInventory.h"
#include "InventoryReqBytes.h"
#include "Scheduler.h"
#include "Storage.h"
#include "UdpService.h"

using namespace std;
using asio::ip::udp;

class InventoryReplyHandler final : public UdpHandler
{
public:
	InventoryReplyHandler(
		uint32_t controller_id,
		const string &address,
		in_port_t port,
		const shared_ptr<Storage> &storage,
		const shared_ptr<UdpService> &service,
		const shared_ptr<Scheduler> &scheduler,
		int ntry
	) : controller_id(controller_id),
	    address(address),
	    port(port),
	    storage(storage),
	    service(service),
	    scheduler(scheduler),
	    ntry(ntry)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		try {
			BytesInventory inventory(reply);
			storage->update(
				fmt::format("/controller/{0}/locks", controller_id),
				nlohmann::json::object({{"locks", inventory.locks()}})
			);
		} catch (const exception &) {
			if (ntry > 0) {
				scheduler->schedule(
					make_shared<InventoryTask>(
						controller_id,
						address,
						port,
						storage,
						service,
						scheduler,
						ntry - 1
					),
					5s
				);
			}
		}
	}
private:
	const uint32_t controller_id;
	const string address;
	const in_port_t port;
	const shared_ptr<Storage> storage;
	const shared_ptr<UdpService> service;
	const shared_ptr<Scheduler> scheduler;
	const int ntry;
};

InventoryTask::InventoryTask(
	uint32_t controller_id,
	const string &address,
	in_port_t port,
	const shared_ptr<Storage> &storage,
	const shared_ptr<UdpService> &service,
	const shared_ptr<Scheduler> &scheduler,
	int ntry
) : controller_id(controller_id),
    address(address),
    port(port),
    storage(storage),
    service(service),
    scheduler(scheduler),
    ntry(ntry)
{
}

void InventoryTask::run() const
{
	service->request(
		address,
		port,
		make_shared<InventoryReqBytes>(),
		make_shared<InventoryReplyHandler>(
			controller_id,
			address,
			port,
			storage,
			service,
			scheduler,
			ntry
		)
	);
}
