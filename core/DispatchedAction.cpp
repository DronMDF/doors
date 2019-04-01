// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "DispatchedAction.h"
#include <cstring>

using namespace std;

DispatchedAction::DispatchedAction(const map<uint32_t, shared_ptr<Action>> &actions)
	: actions(actions)
{
}

bool DispatchedAction::process(
	const vector<uint8_t> &request,
	const shared_ptr<Socket> &socket
) const
{
	if (request.size() < sizeof(uint32_t) * 2) {
		throw runtime_error("Некорректный запрос к сервреру");
	}

	vector<uint32_t> header(2);
	memcpy(&header[0], &request[0], sizeof(uint32_t) * 2);

	return actions.at(be32toh(header[1]))->process(request, socket);
}
