// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BootstrapTask.h"
#include "DefaultStorage.h"

using namespace std;

BootstrapTask::BootstrapTask(
	const shared_ptr<Storage> &storage,
	const shared_ptr<Scheduler> &scheduler
) : storage(storage), scheduler(scheduler)
{
}

void BootstrapTask::run() const
{
	const auto controllers = DefaultStorage(
		storage,
		R"({ "controllers": [] })"_json
	).query("/controllers");
	for (const auto &c [[gnu::unused]] : controllers["controllers"]) {
		// @todo #64 Создать задачу на инвентаризацию контроллера
		//  В структуре содержится адрес и порт
	}
}
