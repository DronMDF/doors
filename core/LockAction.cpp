// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockAction.h"
#include <fmt/format.h>
#include "BytesLock.h"
#include "ErrorBytes.h"
#include "OkBytes.h"
#include "Socket.h"
#include "Storage.h"

using namespace std;

class LockActionStorageHandler final : public StorageHandler {
public:
	LockActionStorageHandler(
		const shared_ptr<const BytesLock> &request,
		const shared_ptr<Socket> &socket
	) : request(request), socket(socket)
	{
	}

	void handle(const shared_ptr<const StorageResponse> &response) const override
	{
		try {
			const auto json = response->json();
			if (json["approve"]) {
				OkBytes ok(request->id(), time(nullptr));
				socket->send(ok.raw());
			} else {
				ErrorBytes error(request->id());
				socket->send(error.raw());
			}
		} catch (const exception &e) {
			ErrorBytes error(request->id());
			socket->send(error.raw());
		}
	}

private:
	const shared_ptr<const BytesLock> request;
	const shared_ptr<Socket> socket;
};

LockAction::LockAction(const shared_ptr<const Storage> &storage)
	: storage(storage)
{
}

bool LockAction::process(const vector<uint8_t> &request, const shared_ptr<Socket> &socket) const
{
	const auto lock = make_shared<BytesLock>(request);
	storage->query(
		fmt::format(
			"/controller/{}/lock/{}/lock?key={}",
			// @todo #132 В запросе не содержится номер контроллера
			//  Его можно определить через сервер БД, но это нужен дополнительный запрос
			0,
			lock->lock_id(),
			lock->key_id()
		),
		make_shared<LockActionStorageHandler>(lock, socket)
	);
	return true;
}
