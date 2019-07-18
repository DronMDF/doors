// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "TracedAction.h"
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

TracedAction::TracedAction(const string &tag, const shared_ptr<const Action> &action)
	: tag(tag), action(action)
{
}

bool TracedAction::process(
	const shared_ptr<const Bytes> &request,
	const shared_ptr<Socket> &socket
) const
{
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	cout << put_time(&tm, "%T") << " " << tag << " action" << endl;
	return action->process(request, socket);
}
