// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <asio/ts/internet.hpp>
#include <core/Socket.h>

class AsioSocket final : public Socket {
public:
	AsioSocket(
		const std::shared_ptr<asio::ip::udp::socket> &socket,
		const asio::ip::udp::endpoint &endpoint
	);

	void send(const std::vector<uint8_t> &packet) const override;

private:
	const std::shared_ptr<asio::ip::udp::socket> socket;
	const asio::ip::udp::endpoint endpoint;
};
