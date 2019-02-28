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

args::Group arguments("Global options");
args::HelpFlag help(arguments, "help", "Display this help menu", {'h', "help"});
args::ValueFlag<int> port(arguments, "port", "communication port", {'p'}, 5000);

// @todo #4 Convert command to class
void inventory_command(args::Subparser *parser)
{
	args::Positional<std::string> ip(*parser, "ip", "Controller ip", args::Options::Required);
	parser->Parse();

	cout << "inventory " << args::get(ip) << ":" << args::get(port) << endl;

	asio::io_context context;

	udp::socket socket(context, udp::endpoint(udp::v4(), 0));

	udp::resolver resolver(context);
	const auto endpoint = *resolver.resolve(
		udp::v4(),
		args::get(ip),
		to_string(args::get(port))
	).begin();

	InventoryRequest request;
	socket.send_to(asio::buffer(&request, sizeof(request)), endpoint);

	uint8_t reply_data[1400];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket.receive_from(asio::buffer(reply_data, 1400), sender_endpoint);

	if (reply_length < sizeof(InventoryReply)) {
		cout << "Wrong Init reply" << endl;
		return;
	}

	InventoryReply *reply = reinterpret_cast<InventoryReply *>(&reply_data[0]);
	if (ntohl(reply->version) != VERSION) {
		cout << "Wrong protool version" << endl;
		return;
	}

	if (ntohl(reply->command) != C2S_INVENTORY) {
		cout << "Wrong Init reply command" << endl;
		return;
	}

	const auto lock_count = ntohl(reply->lock_count);
	if (reply_length < sizeof(InventoryReply) + lock_count * sizeof(uint32_t)) {
		cout << "Wrong Init reply content" << endl;
		return;
	}

	vector<uint32_t> locks(
		reinterpret_cast<uint32_t *>(&reply_data[sizeof(InventoryReply)]),
		reinterpret_cast<uint32_t *>(&reply_data[sizeof(InventoryReply)]) + lock_count
	);

	cout << "Controller: #" << sender_endpoint.address() << endl;
	cout << "Locks:" << endl;
	for (const auto &l : locks) {
		cout << "\t" << ntohl(l) << endl;
	}
}

int main(int argc, char **argv)
{
	args::ArgumentParser parser("Doors utility.", "Footer.");
	args::GlobalOptions globals(parser, arguments);

	args::Group commands(parser, "commands");
	args::Command inventory(
		commands,
		"inventory",
		"Controler inventory",
		[](args::Subparser &parser){ inventory_command(&parser); }
	);


	try {
		parser.ParseCLI(argc, argv);
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
