// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <netinet/in.h>
#include "Task.h"

class Scheduler;
class Storage;
class UdpService;

class InventoryTask final : public Task {
public:
	// @todo #159 Очень много параметров конструктора у InventoryTask.
	//  Одна из идей #134 - объединить адрес и порт, но этого будет мало.
	InventoryTask(
		uint32_t controller_id,
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<Storage> &storage,
		const std::shared_ptr<UdpService> &service,
		const std::shared_ptr<Scheduler> &scheduler,
		int ntry = 3
	);

	void run() const override;
private:
	const uint32_t controller_id;
	const std::string address;
	const in_port_t port;
	const std::shared_ptr<Storage> storage;
	const std::shared_ptr<UdpService> service;
	const std::shared_ptr<Scheduler> scheduler;
	const int ntry;
};
