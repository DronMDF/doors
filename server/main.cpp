// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>
#include <asio/ts/internet.hpp>
#include <protocol.h>
#include <core/BootstrapTask.h>
#include <core/DispatchedAction.h>
#include <core/HttpStorage.h>
#include <core/AsioScheduler.h>
#include <core/Listener.h>
#include <core/LockAction.h>
#include <core/NetIoService.h>
#include <core/StatusAction.h>
#include <core/TracedAction.h>
#include <core/UnlockAction.h>

using namespace std;
using asio::ip::udp;

int main(int argc, char **argv)
{
	args::ArgumentParser parser("Doors server", "Done");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::ValueFlag<in_port_t> port(parser, "port", "communication port", {'p'}, 5000);
	args::ValueFlag<string> uri(parser, "uri", "Config uri", {'u'}, "http://127.0.0.1:8000");

	try {
		parser.ParseCLI(argc, argv);

		asio::io_context io_context;

		const auto service = make_shared<NetIoService>(&io_context);
		const auto scheduler = make_shared<AsioScheduler>(&io_context);
		const auto storage = make_shared<HttpStorage>(args::get(uri), service);

		// Получаем стартовую информацию (из БД)
		scheduler->schedule(make_shared<BootstrapTask>(storage, scheduler, service));

		make_shared<Listener>(
			&io_context,
			args::get(port),
			make_shared<DispatchedAction>(
				UNLOCK,
				make_shared<TracedAction>(
					"UNLOCK",
					make_shared<UnlockAction>()
				),
				LOCK,
				make_shared<TracedAction>(
					"LOCK",
					make_shared<LockAction>()
				),
				KEY_STATUS_REQ,
				make_shared<TracedAction>(
					"STATUS",
					make_shared<StatusAction>(storage, scheduler)
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
