// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryTask.h"
#include <asio/ts/internet.hpp>
#include <fmt/format.h>
#include <protocol.h>
#include "BytesInventory.h"
#include "Storage.h"

using namespace std;
using asio::ip::udp;

InventoryTask::InventoryTask(
	const string &address,
	in_port_t port,
	const shared_ptr<Storage> &storage
) : address(address), port(port), storage(storage)
{
}

void InventoryTask::run() const
{
	// @todo #67 Необходимо производить эту операцию асинхронно
	//  Но проблема в том, что она порождается из booststrap,
	//  который ничего не знает про ioservice... хм
	asio::io_context context;

	udp::socket socket(context, udp::endpoint(udp::v4(), 0));

	udp::resolver resolver(context);
	const auto endpoint = *resolver.resolve(udp::v4(), address, to_string(port)).begin();

	InventoryReq request;
	socket.send_to(asio::buffer(&request, sizeof(request)), endpoint);

	uint8_t reply_data[1400];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket.receive_from(asio::buffer(reply_data, 1400), sender_endpoint);

	BytesInventory inventory(&reply_data[0], reply_length);

	storage->update(
		fmt::format("/controller/{1}:{2}/locks", address, port),
		nlohmann::json::object({{"locks", inventory.locks()}})
	);
}
