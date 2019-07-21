// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "Listener.h"
#include <functional>
#include <iostream>
#include "Action.h"
#include "AsioSocket.h"
#include "RawBytes.h"

using namespace std;
using asio::ip::udp;

Listener::Listener(
	asio::io_context *io_context,
	in_port_t port,
	const std::shared_ptr<const Action> &action
) :
	socket_(
		make_shared<udp::socket>(
			ref(*io_context),
			udp::endpoint(udp::v4(), port))
	),
	data_(1024),
	action(action)
{
}

void Listener::start()
{
	do_receive();
}

void Listener::do_receive()
{
	socket_->async_receive_from(
		asio::buffer(data_),
		sender_endpoint_,
		bind(
			&Listener::handle_receive,
			shared_from_this(),
			placeholders::_1,
			placeholders::_2
		)
	);
}

void Listener::process_request(size_t bytes_recvd)
{
	action->process(
		make_shared<RawBytes>(&data_[0], bytes_recvd),
		make_shared<AsioSocket>(socket_, sender_endpoint_)
	);
}

void Listener::handle_receive(error_code ec, size_t bytes_recvd)
{
	try {
		if (ec) {
			throw system_error(ec, "Unable to receive");
		}

		process_request(bytes_recvd);
	} catch(const exception &e) {
		cout << e.what() << endl;
	}
	do_receive();
}
