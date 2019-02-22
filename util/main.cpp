// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <args.hxx>

using namespace std;

args::Group arguments("Global options");
args::HelpFlag help(arguments, "help", "Display this help menu", {'h', "help"});
args::ValueFlag<int> port(arguments, "port", "communication port", {'p'}, 5000);

// @todo #4 Convert command to class
void inventory_command(args::Subparser *parser)
{
	args::Positional<std::string> ip(*parser, "ip", "Controller ip", args::Options::Required);
	parser->Parse();

	// @todo #4 Make inventory request and parse reply
	cout << "inventory " << args::get(ip) << ":" << args::get(port) << endl;
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
