// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <vector>

class Bytes;
class Socket;

class Action {
public:
	virtual ~Action() = default;

	// @todo #31 При такой реализации DispatchedAction нет необходимости в коде возврата
	virtual bool process(
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<Socket> &socket
	) const = 0;
};
