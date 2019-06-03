// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <netinet/in.h>
#include <core/Task.h>

class Scheduler;
class UdpService;

class LockTask final : public Task {
public:
	LockTask(
		int lock_id,
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<UdpService> &service,
		const std::shared_ptr<Scheduler> &scheduler
	);
	void run() const override;
private:
	int lock_id;
	const std::string address;
	in_port_t port;
	const std::shared_ptr<UdpService> service;
	const std::shared_ptr<Scheduler> scheduler;
};
