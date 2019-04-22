// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BootstrapTask.h"
#include "DefaultStorage.h"
#include "InventoryTask.h"
#include "Scheduler.h"

using namespace std;

BootstrapTask::BootstrapTask(
	const shared_ptr<Storage> &storage,
	const shared_ptr<Scheduler> &scheduler,
	const shared_ptr<IoService> &service
) : storage(storage), scheduler(scheduler), service(service)
{
}

void BootstrapTask::run() const
{
	const auto controllers = DefaultStorage(
		storage,
		R"({ "controllers": [] })"_json
	).query("/controllers");
	for (const auto &c : controllers["controllers"]) {
		scheduler->schedule(
			make_shared<InventoryTask>(
				c["address"].get<string>(),
				c["port"].get<in_port_t>(),
				storage,
				service
			)
		);
	}

	// @todo #67 Нужно поставить отложенную задачу
	//  чтобы провести повторную инвентаризацию через час?
}
