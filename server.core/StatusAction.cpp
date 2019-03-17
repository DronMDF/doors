// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusAction.h"
#include <cstring>
#include <protocol.h>
#include "Scheduler.h"
#include "StatusTask.h"

using namespace std;

StatusAction::StatusAction(const shared_ptr<Scheduler> &scheduler)
	: scheduler(scheduler)
{
}

bool StatusAction::process(const vector<uint8_t> &request, const shared_ptr<Socket> &socket) const
{
	if (request.size() < sizeof(KeyStatusRequest)) {
		return false;
	}

	const auto *req = reinterpret_cast<const KeyStatusRequest *>(&request[0]);
	if (ntohl(req->command) != C2S_KEY_STATUS) {
		return false;
	}

	scheduler->schedule(make_shared<StatusTask>(*req, socket));
	return true;
}
