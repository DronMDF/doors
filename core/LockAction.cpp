// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockAction.h"
#include "BytesLock.h"
#include "OkBytes.h"
#include "Socket.h"

using namespace std;

bool LockAction::process(const vector<uint8_t> &request, const shared_ptr<Socket> &socket) const
{
	BytesLock lock(request);
	// @todo #129 Необходимо подвердить возможность закрытия дынного замка данным ключем
	OkBytes ok(lock.id(), time(nullptr));
	socket->send(ok.raw());
	return true;
}
