// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ImmediatlyScheduler.h"
#include "Task.h"

using namespace std;

void ImmediatlyScheduler::schedule(const shared_ptr<Task> &task) const
{
	task->run();
}
