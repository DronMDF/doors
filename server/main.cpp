// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>
#include <asio/ts/internet.hpp>
#include <server.core/ImmediatlyScheduler.h>
#include <server.core/NullStorage.h>
#include <server.core/StatusAction.h>
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
		// @todo #32: Необходим обобщенный интерфейс к хранилищу.
		// За одним интерфейсом будут скрываться разные операции, как с памятью, так и с 1C.
		make_shared<Listener>(
			&io_context,
			args::get(port),
			// @todo #29 Создать класс диспетчер для разруливания запросов
			make_shared<StatusAction>(
				// @todo #34 Интерфейс для доступа к дефолтным значениям
				//  Пока нет доступа к 1С, БД не должна фейлить запрос, а
				//  должна, с помощью декоратора, возвращать дефолтные значения.
				make_shared<NullStorage>(),
				make_shared<ImmediatlyScheduler>()
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
