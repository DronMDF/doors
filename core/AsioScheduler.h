// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <asio/ts/internet.hpp>
#include "Scheduler.h"

class AsioScheduler final : public Scheduler {
public:
	explicit AsioScheduler(asio::io_context *io_context);
	void schedule(const std::shared_ptr<Task> &task) const override;
private:
	asio::io_context *io_context;
};
