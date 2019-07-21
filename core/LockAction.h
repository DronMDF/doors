// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Action.h"

class Storage;

class LockAction final : public Action {
public:
	explicit LockAction(const std::shared_ptr<const Storage> &storage);
	void process(
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<Socket> &socket
	) const override;
private:
	const std::shared_ptr<const Storage> storage;
};
