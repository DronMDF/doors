// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <iomanip>
#include <args.hxx>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <protocol.h>
#include <core/BytesInventory.h>

using namespace std;
using asio::ip::udp;

args::Group arguments("Global options");
args::HelpFlag help(arguments, "help", "Display this help menu", {'h', "help"});
args::ValueFlag<int> port(arguments, "port", "communication port", {'p'}, 5000);

// @todo #4 Convert command to class

// @todo #27 Много однообразных операций по проверке
//  Можно ли все команды инкапсулировать в одном классе?
//  Но поскольку наборы полей разные -
//  не все операции в этом классе будут применимы в одинаковой степени.
//  Или всетаки на каждую команду отдельный враппер?
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

	InventoryReq request;
	socket.send_to(asio::buffer(&request, sizeof(request)), endpoint);

	uint8_t reply_data[1400];
	udp::endpoint sender_endpoint;
	// @todo #2 Необходимо установить таймаут на данную операцию.
	//  3 секунды наверное хватит c головой
	size_t reply_length = socket.receive_from(asio::buffer(reply_data, 1400), sender_endpoint);

	cout << "Controller: #" << sender_endpoint.address() << endl;

	BytesInventory inventory(&reply_data[0], reply_length);
	cout << "Locks:" << endl;
	for (const auto &l : inventory.locks()) {
		cout << "\t" << l << endl;
	}
}

void status_command(args::Subparser *parser)
{
	args::Positional<std::string> ip(*parser, "ip", "Controller ip", args::Options::Required);
	args::Positional<std::string> token(*parser, "token", "Token", args::Options::Required);
	parser->Parse();

	uint64_t key = 0;
	istringstream in(args::get(token));
	in >> hex >> key;

	cout << "status " << args::get(ip) << ":" << args::get(port)
		<< ", token "  << hex << setw(16) << setfill('0') << key << endl;

	asio::io_context context;

	udp::socket socket(context, udp::endpoint(udp::v4(), 0));

	udp::resolver resolver(context);
	const auto endpoint = *resolver.resolve(
		udp::v4(),
		args::get(ip),
		to_string(args::get(port))
	).begin();

	KeyStatusRequest request;
	request.key = htobe64(key);
	socket.send_to(asio::buffer(&request, sizeof(request)), endpoint);

	uint8_t reply_data[1400];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket.receive_from(asio::buffer(reply_data, 1400), sender_endpoint);

	if (reply_length < sizeof(KeyStatus)) {
		cout << "Wrong KeyStatus reply" << endl;
		return;
	}

	KeyStatus *reply = reinterpret_cast<KeyStatus *>(&reply_data[0]);
	if (ntohl(reply->version) != VERSION) {
		cout << "Wrong protool version" << endl;
		return;
	}

	if (ntohl(reply->command) != KEY_STATUS) {
		cout << "Wrong KeyStatus reply command" << endl;
		return;
	}

	// @todo #52 Необходим BytesKeyStatus для разбора входящих запросов
	const auto lock_count = 0;		// be32toh(reply->lock_count);
	if (reply_length < sizeof(KeyStatus) + lock_count * sizeof(uint32_t)) {
		cout << "Wrong Init reply content" << endl;
		return;
	}

	cout << "Контракт: "
		<< hex << setw(16) << setfill('0') << be64toh(reply->contract) << endl;
	cout << "Срок действия до: " << be32toh(reply->expired) << endl;
	cout << "Баланс: " << be32toh(reply->money) << "коп" << endl;

	vector<uint32_t> locks(
		reinterpret_cast<uint32_t *>(&reply_data[sizeof(KeyStatus)]),
		reinterpret_cast<uint32_t *>(&reply_data[sizeof(KeyStatus)]) + lock_count
	);

	cout << "Locks:" << endl;
	for (const auto &l : locks) {
		cout << "\t" << be32toh(l) << endl;
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
	args::Command status(
		commands,
		"status",
		"Status",
		[](args::Subparser &parser){ status_command(&parser); }
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
