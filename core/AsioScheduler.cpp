// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "AsioScheduler.h"
#include "Task.h"

using namespace std;

AsioScheduler::AsioScheduler(asio::io_context *io_context)
	: io_context(io_context)
{
}

void AsioScheduler::schedule(
	const shared_ptr<Task> &task,
	const chrono::steady_clock::duration &delay [[gnu::unused]]
) const
{
	// @todo #113 Если delay определен - операцию нужно производить
	//  после того, как выйдет отведенное время.
	//  Не блокируюя естественно остальные.
	asio::post(*io_context, [task]{ task->run(); });
}
