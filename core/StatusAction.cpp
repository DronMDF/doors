// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusAction.h"
#include <cstring>
#include <protocol.h>
#include "Bytes.h"
#include "Scheduler.h"
#include "StatusTask.h"

using namespace std;

StatusAction::StatusAction(
	const shared_ptr<Storage> &storage,
	const shared_ptr<Scheduler> &scheduler
)
	: storage(storage), scheduler(scheduler)
{
}

void StatusAction::process(
	const shared_ptr<const Bytes> &request,
	const shared_ptr<Socket> &socket
) const
{
	const auto raw = request->raw();
	if (raw.size() < sizeof(KeyStatusRequest)) {
		throw runtime_error("Key status request too small");
	}

	const auto *req = reinterpret_cast<const KeyStatusRequest *>(&raw[0]);
	if (ntohl(req->command) != KEY_STATUS_REQ) {
		throw runtime_error("Wrong code for key status request");
	}

	scheduler->schedule(make_shared<StatusTask>(*req, socket, storage));
}
