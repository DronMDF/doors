// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <core/UdpService.h>

class Scheduler;

class UnlockTaskHandler final :
	public UdpHandler,
	public std::enable_shared_from_this<UnlockTaskHandler>
{
public:
	UnlockTaskHandler(
		int lock_id,
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<UdpService> &service,
		const std::shared_ptr<Scheduler> &scheduler
	);

	void handle(const std::shared_ptr<const Bytes> &reply) const override;
private:
	int lock_id;
	const std::string address;
	in_port_t port;
	const std::shared_ptr<UdpService> service;
	const std::shared_ptr<Scheduler> scheduler;
};
