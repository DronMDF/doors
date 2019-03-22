// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <protocol.h>
#include "Task.h"

class Socket;
class Storage;

class StatusTask final : public Task {
public:
	StatusTask(
		const KeyStatusRequest &request,
		const std::shared_ptr<Socket> &socket,
		const std::shared_ptr<Storage> &storage
	);

	void run() const override;
private:
	const KeyStatusRequest request;
	const std::shared_ptr<Socket> socket;
	const std::shared_ptr<Storage> storage;
};
