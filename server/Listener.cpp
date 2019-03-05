// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "Listener.h"
#include <functional>
#include <iostream>
#include "Action.h"

using namespace std;
using asio::ip::udp;

Listener::Listener(
	asio::io_context *io_context,
	in_port_t port,
	const std::shared_ptr<const Action> &action
) : socket_(*io_context, udp::endpoint(udp::v4(), port)), data_(1024), action(action)
{
}

void Listener::start()
{
	do_receive();
}

void Listener::do_receive()
{
	socket_.async_receive_from(
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
	auto et = data_.begin();
	advance(et, bytes_recvd);
	// @todo #21 Необходимо создать объект-сокет, в который можно будет отправлять данные
	//  Причем делать это не сейчас и синхронно, а потом. И этот объект съест do_send
	if (!action->process(vector<uint8_t>(data_.begin(), et), {})) {
		throw runtime_error("Unknown request command");
	}
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

void Listener::do_send(size_t length)
{
	socket_.async_send_to(
		asio::buffer(data_, length),
		sender_endpoint_,
		bind(
			&Listener::handle_send,
			shared_from_this(),
			placeholders::_1,
			placeholders::_2
		)
	);
}

void Listener::handle_send(error_code ec [[gnu::unused]], size_t bytes_sent [[gnu::unused]])
{
	do_receive();
}
