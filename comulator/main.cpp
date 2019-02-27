// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <Protocol.h>

using namespace std;
using asio::ip::udp;

class server
{
public:
	server(asio::io_context *io_context, in_port_t port)
		: socket_(*io_context, udp::endpoint(udp::v4(), port)), data_(1024)
	{
		do_receive();
	}

	void do_receive()
	{
		socket_.async_receive_from(
			asio::buffer(data_),
			sender_endpoint_,
		        [this](error_code ec, size_t bytes_recvd) {
				if (!ec && bytes_recvd > 0) {
					do_send(bytes_recvd);
				} else {
					do_receive();
				}
			}
		);
	}

	void do_send(size_t length)
	{
		// @todo #3 Этот класс взят из примера и отвечает эхом
		//  Должен эмулировать поведение реального замка
		//  и отвечать на запрос инвентаризации
		socket_.async_send_to(
			asio::buffer(data_, length),
			sender_endpoint_,
			[this](error_code /*ec*/, size_t /*bytes_sent*/) {
				do_receive();
			}
		);
	}

private:
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	vector<uint8_t> data_;
};

int main(int argc, char **argv)
{
	args::ArgumentParser parser("Doors controller emulator", "Done");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::ValueFlag<in_port_t> port(parser, "port", "communication port", {'p'}, 5000);

	try {
		parser.ParseCLI(argc, argv);

		asio::io_context io_context;
		server s(&io_context, args::get(port));
		io_context.run();
	} catch (const args::Help &) {
		cout << parser;
		return EXIT_SUCCESS;
	} catch (const args::ParseError &e) {
		cerr << e.what() << std::endl;
		cerr << parser;
		return EXIT_FAILURE;
	} catch (const args::ValidationError &e) {
		cerr << e.what() << std::endl;
		cerr << parser;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
