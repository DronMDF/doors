// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockTask.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/List32Bytes.h>
#include <core/IoService.h>
#include <core/UdpHandler.h>

using namespace std;

class LockReplyHandler final : public UdpHandler {
public:
	explicit LockReplyHandler(int lock_no)
		: lock_no(lock_no)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		// @todo #113 В обработчике LockReplyHandler логика на исключениях
		//  Может быть мне в качестве коллбеков к сервису навешивать экшины?
		//  Там можно использовать DispatchedAction и разруливать запросы...
		try {
			BytesOk status(reply->raw());
			cout << "Lock " << lock_no << " is locked" << endl;
			// @todo #113 Если замок открылся - нужно запланировать закрытие
		} catch (const exception &e) {
			cout << "Lock " << lock_no << " is not locked" << endl;
			// @todo #113 Если замок не открылся - нужно повторно обратиться к серверу.
			//  Но эти попытки должны быть ограничены
		}
	}
private:
	int lock_no;
};

LockTask::LockTask(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<IoService> &service,
	const shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void LockTask::run() const
{
	service->async_udp_request(
		address,
		port,
		// @todo #113 Требуется реализация LockBytes
		//  make_shared<LockBytes>(lock_id, 0x123456789ABCDEF),
		make_shared<List32Bytes>(vector<uint32_t>{1, 2}),
		make_shared<LockReplyHandler>(lock_id)
	);
}
