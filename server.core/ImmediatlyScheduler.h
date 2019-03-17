// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Scheduler.h"

class ImmediatlyScheduler final : public Scheduler {
public:
	void schedule(const std::shared_ptr<Task> &task) const override;
};
