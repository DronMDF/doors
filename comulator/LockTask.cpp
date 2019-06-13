// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockTask.h"
#include <core/LockBytes.h>
#include <core/UdpService.h>
#include "LockTaskHandler.h"
#include "UnlockTask.h"

using namespace std;

LockTask::LockTask(
	int lock_id,
	const string &address,
	in_port_t port,
	const shared_ptr<UdpService> &service,
	const shared_ptr<const UdpHandler> &handler
) : lock_id(lock_id), address(address), port(port), service(service), handler(handler)
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
		handler
	);
}
