// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <protocol.h>

using namespace std;
using asio::ip::udp;

// @todo #13 Вынести класс в отдельный файл, и переименовать заодно.
class server final : public enable_shared_from_this<server>
{
public:
	server(asio::io_context *io_context, in_port_t port)
		: socket_(*io_context, udp::endpoint(udp::v4(), port)), data_(1024)
	{
	}

	void start()
	{
		do_receive();
	}

	void do_receive()
	{
		socket_.async_receive_from(
			asio::buffer(data_),
			sender_endpoint_,
			bind(
				&server::handle_receive,
				shared_from_this(),
				placeholders::_1,
				placeholders::_2
			)
		);
	}

	void process_request(size_t bytes_recvd)
	{
		if (bytes_recvd < sizeof(uint32_t) * 2) {
			throw runtime_error("Invalid request");
		}

		const auto *req = reinterpret_cast<InventoryReq *>(&data_[0]);
		if (ntohl(req->version) != VERSION) {
			throw runtime_error("Invalid request version");
		}

		if (ntohl(req->command) == INVENTORY_REQ) {
			Inventory reply;
			// @todo #13 Наполнить ответ содержимым
			//  и содержимое должно соответствоать настройкам эмулятора.
			memcpy(&data_[0], &reply, sizeof(reply));
			do_send(sizeof(reply));
			return;
		}

		throw runtime_error("Unknown request command");
	}

	void handle_receive(error_code ec, size_t bytes_recvd)
	{
		try {
			if (ec) {
				throw system_error(ec, "Unable to receive");
			}

			process_request(bytes_recvd);
			return;
		} catch(const exception &e) {
			cout << e.what() << endl;
		}
		do_receive();
	}

	void do_send(size_t length)
	{
		socket_.async_send_to(
			asio::buffer(data_, length),
			sender_endpoint_,
			bind(
				&server::handle_send,
				shared_from_this(),
				placeholders::_1,
				placeholders::_2
			)
		);
	}

	void handle_send(error_code ec [[gnu::unused]], size_t bytes_sent [[gnu::unused]])
	{
		do_receive();
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
		make_shared<server>(&io_context, args::get(port))->start();
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
