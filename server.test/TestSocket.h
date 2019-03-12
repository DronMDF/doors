// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <server/Socket.h>

class TestSocket final : public Socket {
public:
	explicit TestSocket(std::vector<uint8_t> * const packet);

	void send(const std::vector<uint8_t> &packet) const override;
private:
	std::vector<uint8_t> * const packet;
};
