// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "AsioSocket.h"
#include <functional>
#include <asio/ts/buffer.hpp>

using namespace std;
using asio::ip::udp;

class AsioSendHandler final {
public:
	explicit AsioSendHandler(const vector<uint8_t> &packet)
		: packet(packet)
	{
	}

	asio::const_buffer buffer() const
	{
		return asio::buffer(packet);
	}

	void handler(error_code ec [[gnu::unused]], size_t bytes_sent [[gnu::unused]])
	{
	}

private:
	const vector<uint8_t> packet;
};

AsioSocket::AsioSocket(
	const shared_ptr<asio::ip::udp::socket> &socket,
	const asio::ip::udp::endpoint &endpoint
) : socket(socket), endpoint(endpoint)
{
}

void AsioSocket::send(const vector<uint8_t> &packet) const
{
	auto handler = make_shared<AsioSendHandler>(packet);
	socket->async_send_to(
		handler->buffer(),
		endpoint,
		bind(&AsioSendHandler::handler, handler, placeholders::_1, placeholders::_2)
	);
}
