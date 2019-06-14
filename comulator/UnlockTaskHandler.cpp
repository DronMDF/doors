// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "UnlockTaskHandler.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/Scheduler.h>
#include "LockTask.h"
#include "LockTaskHandler.h"
#include "UnlockTask.h"

using namespace std;

UnlockTaskHandler::UnlockTaskHandler(
	int lock_id,
	const std::string &address,
	in_port_t port,
	const std::shared_ptr<UdpService> &service,
	const std::shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void UnlockTaskHandler::handle(const shared_ptr<const Bytes> &reply) const
{
	try {
		BytesOk status(reply->raw());
		cout << "Lock " << lock_id << " is unlocked" << endl;
		scheduler->schedule(
			make_shared<LockTask>(
				lock_id,
				address,
				port,
				service,
				make_shared<LockTaskHandler>(
					lock_id,
					address,
					port,
					service,
					scheduler
				)
			),
			1min
		);
	} catch (const exception &e) {
		cout << "Lock " << lock_id << " is not unlocked" << endl;
		scheduler->schedule(
			make_shared<UnlockTask>(
				lock_id,
				address,
				port,
				service,
				shared_from_this()
			),
			10s
		);
	}
}
