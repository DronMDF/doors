// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>
#include <asio/ts/internet.hpp>
#include <protocol.h>
#include <core/DispatchedAction.h>
#include <core/ImmediatlyScheduler.h>
#include <core/NullStorage.h>
#include <core/StatusAction.h>
#include "Listener.h"

using namespace std;
using asio::ip::udp;

int main(int argc, char **argv)
{
	args::ArgumentParser parser("Doors server", "Done");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::ValueFlag<in_port_t> port(parser, "port", "communication port", {'p'}, 5000);

	try {
		parser.ParseCLI(argc, argv);

		asio::io_context io_context;
		make_shared<Listener>(
			&io_context,
			args::get(port),
			make_shared<DispatchedAction>(
				KEY_STATUS_REQ,
				make_shared<StatusAction>(
					make_shared<NullStorage>(),
					make_shared<ImmediatlyScheduler>()
				)
			)
		)->start();
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
