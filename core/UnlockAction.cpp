// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "UnlockAction.h"
#include <fmt/format.h>
#include "BytesUnlock.h"
#include "ErrorBytes.h"
#include "OkBytes.h"
#include "Socket.h"
#include "Storage.h"

using namespace std;

class UnlockActionStorageHandler final : public StorageHandler {
public:
	UnlockActionStorageHandler(
		const shared_ptr<const BytesUnlock> &request,
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
	// @todo #136 В классе UnlockActionStorageHandler и в классе LockActionStorageHandler
	//  достаточно передать идентификатор запроса. Tаскать весь запрос с собой не обязательно.
	const shared_ptr<const BytesUnlock> request;
	const shared_ptr<Socket> socket;
};

UnlockAction::UnlockAction(const shared_ptr<const Storage> &storage)
	: storage(storage)
{
}

bool UnlockAction::process(const vector<uint8_t> &request, const shared_ptr<Socket> &socket) const
{
	const auto unlock = make_shared<BytesUnlock>(request);
	storage->query(
		fmt::format(
			"/controller/{}/lock/{}/unlock?key={}",
			// @todo #136 В unlock запросе не содержится номер контроллера
			//  Его можно определить через сервер БД, но это нужен дополнительный запрос
			0,
			unlock->lock_id(),
			unlock->key_id()
		),
		make_shared<UnlockActionStorageHandler>(unlock, socket)
	);
	return true;
}
