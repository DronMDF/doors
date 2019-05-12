// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BootstrapTask.h"
#include "DefaultStorage.h"
#include "InventoryTask.h"
#include "Scheduler.h"

using namespace std;

class BootstrapStorageHandler final : public StorageHandler {
public:
	BootstrapStorageHandler(
		const shared_ptr<IoService> &service,
		const shared_ptr<Scheduler> &scheduler,
		const shared_ptr<Storage> &storage
	) : service(service), scheduler(scheduler), storage(storage)
	{
	}

	void handle(const nlohmann::json &data) const override
	{
		for (const auto &c : data["controllers"]) {
			scheduler->schedule(
				make_shared<InventoryTask>(
					c["id"].get<uint32_t>(),
					c["address"].get<string>(),
					c["port"].get<in_port_t>(),
					storage,
					service
				)
			);
		}
	}

private:
	const shared_ptr<IoService> service;
	const shared_ptr<Scheduler> scheduler;
	const shared_ptr<Storage> storage;
};

BootstrapTask::BootstrapTask(
	const shared_ptr<Storage> &storage,
	const shared_ptr<Scheduler> &scheduler,
	const shared_ptr<IoService> &service
) : storage(storage), scheduler(scheduler), service(service)
{
}

void BootstrapTask::run() const
{
	DefaultStorage(
		storage,
		R"({ "controllers": [] })"_json
	).query(
		"/controller/",
		make_shared<BootstrapStorageHandler>(service, scheduler, storage)
	);

	// @todo #67 Нужно поставить отложенную задачу
	//  чтобы провести повторную инвентаризацию через час?
}
