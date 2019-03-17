// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusTask.h"
#include <cstring>
#include <vector>
#include "Socket.h"

using namespace std;

StatusTask::StatusTask(const KeyStatusRequest &request, const shared_ptr<Socket> &socket)
	: request(request), socket(socket)
{
}

void StatusTask::run() const
{
	KeyStatusReply reply;
	reply.key = request.key;
	// @todo #21 Необходимо по номеру ключа достать всю необходимую информацию из БД,
	//  или из кеша.

	vector<uint8_t> rv(sizeof(reply));
	memcpy(&rv[0], &reply, sizeof(reply));
	socket->send(rv);
}
