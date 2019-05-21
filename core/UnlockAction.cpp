// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "UnlockAction.h"
#include "BytesUnlock.h"
#include "OkBytes.h"
#include "Socket.h"

using namespace std;

bool UnlockAction::process(const vector<uint8_t> &request, const shared_ptr<Socket> &socket) const
{
	BytesUnlock unlock(request);
	// @todo #131 Необходимо подвердить возможность открытия дынного замка данным ключем
	OkBytes ok(unlock.id(), time(nullptr));
	socket->send(ok.raw());
	return true;
}
