// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Task.h"

class IoService;
class Scheduler;
class Storage;

class BootstrapTask final : public Task {
public:
	BootstrapTask(
		const std::shared_ptr<Storage> &storage,
		const std::shared_ptr<Scheduler> &scheduler,
		const std::shared_ptr<IoService> &service
	);
	void run() const override;
private:
	const std::shared_ptr<Storage> storage;
	const std::shared_ptr<Scheduler> scheduler;
	const std::shared_ptr<IoService> service;
};
