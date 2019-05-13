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

void AsioScheduler::schedule(const shared_ptr<Task> &task) const
{
	asio::post(*io_context, [task]{ task->run(); });
}
