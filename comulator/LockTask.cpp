// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockTask.h"
#include <iostream>
#include <core/Bytes.h>
#include <core/BytesOk.h>
#include <core/LockBytes.h>
#include <core/Scheduler.h>
#include <core/UdpService.h>
#include "UnlockTask.h"

using namespace std;

class LockReplyHandler final : public UdpHandler {
public:
	explicit LockReplyHandler(
		int lock_id,
		const shared_ptr<Scheduler> &scheduler,
		const shared_ptr<Task> &task
	) : lock_id(lock_id), scheduler(scheduler), task(task)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		// @todo #113 В обработчике LockReplyHandler логика на исключениях
		//  Может быть мне в качестве коллбеков к сервису навешивать экшины?
		//  Там можно использовать DispatchedAction и разруливать запросы...
		try {
			BytesOk status(reply->raw());
			cout << "Lock " << lock_id << " is locked" << endl;
			scheduler->schedule(task, 3min);
		} catch (const exception &e) {
			cout << "Lock " << lock_id << " is not locked" << endl;
			// @todo #113 Если замок не открылся - нужно повторно обратиться к серверу.
			//  Но эти попытки должны быть ограничены
		}
	}

private:
	int lock_id;
	const shared_ptr<Scheduler> scheduler;
	const shared_ptr<Task> task;
};

LockTask::LockTask(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<Scheduler> &scheduler
) : lock_id(lock_id), address(address), port(port), service(service), scheduler(scheduler)
{
}

void LockTask::run() const
{
	// @todo #123 Для UDP сервиса адрес и порт напрашиваются в инкапсуляцию.
	//  Довольно неудобно постоянно таскать их по всем классам.
	//  Вероятно мы можем сделать базовый udp_io, и навешивать на него адрес endpoint,
	//  чтобы минимизировать количество параметров в данных классах
	//  И если говорим про запросы - этот сокет можно заранее открыть и всегда пользоваться им.
	service->request(
		address,
		port,
		make_shared<LockBytes>(0, lock_id, 0x123456789ABCDEF),
		make_shared<LockReplyHandler>(
			lock_id,
			scheduler,
			make_shared<UnlockTask>(lock_id, address, port, service, scheduler)
		)
	);
}
