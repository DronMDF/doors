// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <chrono>
#include <iostream>
#include <args.hxx>
#include <asio/ts/internet.hpp>
#include <protocol.h>
#include <core/AsioScheduler.h>
#include <core/DispatchedAction.h>
#include <core/InventoryAction.h>
#include <core/Listener.h>
#include <core/AsioUdpService.h>
#include <core/PredefinedStorage.h>
#include <core/TracedAction.h>
#include "Benchmark.h"
#include "BenchmarkHandler.h"
#include "LockTask.h"
#include "LockTaskHandler.h"

using namespace std;

int main(int argc, char **argv)
{
	args::ArgumentParser parser("Doors controller emulator", "Done");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::ValueFlag<in_port_t> port(parser, "port", "communication port", {'p'}, 5000);
	args::ValueFlag<string> saddr(parser, "saddr", "server addr", {'S'}, "127.0.0.1");
	args::ValueFlag<in_port_t> sport(parser, "sport", "server port", {'P'}, 5000);
	args::ValueFlag<int> lock_count(parser, "lock_count", "Locks count", {'l'}, 10);
	args::Flag benchmark(parser, "benchmark", "Stress lock/unlock requests", {'b'});

	try {
		parser.ParseCLI(argc, argv);

		asio::io_context io_context;
		const auto service = make_shared<AsioUdpService>(&io_context);
		const auto scheduler = make_shared<AsioScheduler>(&io_context);

		vector<int> locks;
		for (int i = 0; i < args::get(lock_count); i++) {
			locks.push_back(i + 1);
		}

		if (benchmark) {
			const auto stats = make_shared<BenchmarkStats>(locks.size());
			const auto benchserv = make_shared<BenchmarkUdpService>(service, stats);

			for (const auto &l : locks) {
				scheduler->schedule(
					make_shared<LockTask>(
						l,
						args::get(saddr),
						args::get(sport),
						benchserv,
						make_shared<BenchmarkHandler>(
							l,
							args::get(saddr),
							args::get(sport),
							benchserv,
							scheduler
						)
					)
				);
			}
		} else {
			for (const auto &l : locks) {
				scheduler->schedule(
					make_shared<LockTask>(
						l,
						args::get(saddr),
						args::get(sport),
						service,
						make_shared<LockTaskHandler>(
							l,
							args::get(saddr),
							args::get(sport),
							service,
							scheduler
						)
					),
					1min * l
				);
			}
		}

		make_shared<Listener>(
			&io_context,
			args::get(port),
			make_shared<DispatchedAction>(
				INVENTORY_REQ,
				make_shared<TracedAction>(
					"INVENTORY",
					make_shared<InventoryAction>(
						make_shared<PredefinedStorage>(
							"/locks",
							nlohmann::json{{"locks", locks}}
						)
					)
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
