// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "AsioScheduler.h"
#include <functional>
#include "Task.h"

using namespace std;

class AsioDelayTask final : public enable_shared_from_this<AsioDelayTask> {
public:
	AsioDelayTask(
		asio::io_context *io_context,
		const chrono::steady_clock::duration &delay,
		const shared_ptr<Task> &task
	) : timer(*io_context, delay), task(task)
	{
	}

	void start()
	{
		timer.async_wait(
			bind(&AsioDelayTask::handle, shared_from_this(), placeholders::_1)
		);
	}

	void handle(const error_code &e)
	{
		// @todo #121 Необходимо куда-то выводить ошибки,
		//  Но для этого нужен специальный канал для вывода ошибок.
		//  На экран их печатать нельзя.
		if (!e) {
			task->run();
		}
	}

private:
	asio::steady_timer timer;
	const shared_ptr<Task> task;
};

AsioScheduler::AsioScheduler(asio::io_context *io_context)
	: io_context(io_context)
{
}

void AsioScheduler::schedule(
	const shared_ptr<Task> &task,
	const chrono::steady_clock::duration &delay
) const
{
	if (delay < 1ms) {
		asio::post(*io_context, [task]{ task->run(); });
	} else {
		make_shared<AsioDelayTask>(io_context, delay, task)->start();
	}
}
