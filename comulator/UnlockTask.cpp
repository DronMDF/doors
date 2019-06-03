// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "UnlockTask.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/Scheduler.h>
#include <core/UdpService.h>
#include <core/UnlockBytes.h>
#include "LockTask.h"

using namespace std;

class UnlockReplyHandler final : public UdpHandler {
public:
	explicit UnlockReplyHandler(
		int lock_id,
		const shared_ptr<Scheduler> &scheduler,
		const shared_ptr<Task> &task
	) : lock_id(lock_id), scheduler(scheduler), task(task)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		try {
			BytesOk status(reply->raw());
			cout << "Lock " << lock_id << " is unlocked" << endl;
			scheduler->schedule(task, 1min);
		} catch (const exception &e) {
			cout << "Lock " << lock_id << " is not unlocked" << endl;
		}
	}
private:
	int lock_id;
	const shared_ptr<Scheduler> scheduler;
	const shared_ptr<Task> task;
};

UnlockTask::UnlockTask(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void UnlockTask::run() const
{
	service->request(
		address,
		port,
		make_shared<UnlockBytes>(0, lock_id, 0x123456789ABCDEF),
		make_shared<UnlockReplyHandler>(
			lock_id,
			scheduler,
			make_shared<LockTask>(lock_id, address, port, service, scheduler)
		)
	);
}
