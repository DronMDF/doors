// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <vector>

class Socket;

class Action {
public:
	virtual ~Action() = default;

	virtual bool process(
		const std::vector<uint8_t> &request,
		const std::shared_ptr<Socket> &socket
	) const = 0;
};
