// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <chrono>
#include <memory>

class Task;

class Scheduler {
public:
	virtual ~Scheduler() = default;

	virtual void schedule(
		const std::shared_ptr<Task> &task,
		const std::chrono::steady_clock::duration &delay = {}
	) const = 0;
};
