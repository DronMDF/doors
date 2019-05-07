// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <netinet/in.h>
#include "Task.h"

class IoService;
class Storage;

class InventoryTask final : public Task {
public:
	InventoryTask(
		uint32_t controller_id,
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<Storage> &storage,
		const std::shared_ptr<IoService> &service
	);

	void run() const override;
private:
	const uint32_t controller_id;
	const std::string address;
	const in_port_t port;
	const std::shared_ptr<Storage> storage;
	const std::shared_ptr<IoService> service;
};
