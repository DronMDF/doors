// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusTask.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>
#include "DefaultStorage.h"
#include "Socket.h"
#include "Storage.h"

using namespace std;

StatusTask::StatusTask(
	const KeyStatusRequest &request,
	const shared_ptr<Socket> &socket,
	const shared_ptr<Storage> &storage
) : request(request), socket(socket), storage(storage)
{
}

void StatusTask::run() const
{
	ostringstream query;
	query << "/status/" << hex << setw(16) << setfill('0') << be64toh(request.key);
	const auto data = DefaultStorage(
		storage,
		R"({
			"contract": 0,
			"expired": 0,
			"money": 0,
			"locks": []
		})"_json
	).query(query.str());

	vector<uint32_t> locks;
	for (const auto &l : data["locks"]) {
		locks.push_back(htobe32(l.get<uint32_t>()));
	}

	KeyStatus reply;
	reply.id = request.id;
	reply.key = request.key;
	reply.contract = htobe64(data["contract"].get<uint32_t>());
	reply.expired = htobe32(data["expired"].get<uint32_t>());
	reply.money = htobe32(data["money"].get<uint32_t>());
	reply.lock_count = htobe32(locks.size());

	vector<uint8_t> rv(sizeof(reply) + locks.size() * sizeof(uint32_t));
	memcpy(&rv[0], &reply, sizeof(reply));
	memcpy(&rv[sizeof(reply)], &locks[0], locks.size() * sizeof(uint32_t));
	socket->send(rv);
}
