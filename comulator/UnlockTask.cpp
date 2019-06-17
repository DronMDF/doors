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
#include "LockTaskHandler.h"

using namespace std;

UnlockTask::UnlockTask(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<const UdpHandler> &handler
) : lock_id(lock_id), address(address), port(port), service(service), handler(handler)
{
}

void UnlockTask::run() const
{
	service->request(
		address,
		port,
		make_shared<UnlockBytes>(0, lock_id, 0x123456789ABCDEF),
		handler
	);
}
