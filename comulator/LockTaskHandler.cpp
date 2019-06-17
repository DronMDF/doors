// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockTaskHandler.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/Scheduler.h>
#include "LockTask.h"
#include "UnlockTask.h"
#include "UnlockTaskHandler.h"

using namespace std;

LockTaskHandler::LockTaskHandler(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void LockTaskHandler::handle(const shared_ptr<const Bytes> &reply) const
{
	// @todo #113 В обработчике LockReplyHandler логика на исключениях
	//  Может быть мне в качестве коллбеков к сервису навешивать экшины?
	//  Там можно использовать DispatchedAction и разруливать запросы...
	try {
		BytesOk status(reply->raw());
		cout << "Lock " << lock_id << " is locked" << endl;
		scheduler->schedule(
			make_shared<UnlockTask>(
				lock_id,
				address,
				port,
				service,
				make_shared<UnlockTaskHandler>(
					lock_id,
					address,
					port,
					service,
					scheduler
				)
			),
			3min
		);
	} catch (const exception &e) {
		cout << "Lock " << lock_id << " is not locked" << endl;
		// @todo #113 Если замок не открылся - нужно повторно обратиться к серверу.
		//  Но эти попытки должны быть ограничены
		scheduler->schedule(
			make_shared<LockTask>(lock_id, address, port, service, shared_from_this()),
			10s
		);
	}
}
