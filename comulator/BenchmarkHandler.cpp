// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BenchmarkHandler.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/Scheduler.h>
#include "Benchmark.h"
#include "LockTask.h"
#include "UnlockTask.h"

using namespace std;

BenchmarkHandler::BenchmarkHandler(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void BenchmarkHandler::handle(const shared_ptr<const Bytes> &reply) const
{
	try {
		BytesOk status(reply->raw());
		scheduler->schedule(
			make_shared<UnlockTask>(lock_id, address, port, service, shared_from_this())
		);
	} catch (const exception &e) {
		scheduler->schedule(
			make_shared<LockTask>(lock_id, address, port, service, shared_from_this())
		);
	}
}
