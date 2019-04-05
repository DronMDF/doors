// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusTask.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>
#include "ChainBytes.h"
#include "DefaultStorage.h"
#include "KeyStatusBytes.h"
#include "List32Bytes.h"
#include "Socket.h"

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
		locks.push_back(l.get<uint32_t>());
	}

	ChainBytes rv(
		make_shared<KeyStatusBytes>(
			be32toh(request.id),
			be64toh(request.key),
			data["contract"].get<uint32_t>(),
			data["expired"].get<uint32_t>(),
			data["money"].get<uint32_t>()
		),
		// @todo #52 List32Bytes должен принимать на вход json array
		make_shared<List32Bytes>(locks)
	);
	socket->send(rv.raw());
}
