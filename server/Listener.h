// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <memory>
#include <vector>
#include <asio/ts/internet.hpp>


class Listener final : public std::enable_shared_from_this<Listener>
{
public:
	Listener(asio::io_context *io_context, in_port_t port);
	void start();
private:
	void do_receive();
	void handle_receive(std::error_code ec, size_t bytes_recvd);
	void process_request(size_t bytes_recvd);
	void do_send(size_t length);
	void handle_send(std::error_code ec, size_t bytes_sent);

	asio::ip::udp::socket socket_;
	asio::ip::udp::endpoint sender_endpoint_;
	std::vector<uint8_t> data_;
};
