// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "DispatchedAction.h"
#include <cstring>
#include "Bytes.h"

using namespace std;

DispatchedAction::DispatchedAction(const map<uint32_t, shared_ptr<Action>> &actions)
	: actions(actions)
{
}

bool DispatchedAction::process(
	const shared_ptr<const Bytes> &request,
	const shared_ptr<Socket> &socket
) const
{
	const auto raw = request->raw();
	if (raw.size() < sizeof(uint32_t) * 2) {
		throw runtime_error("Некорректный запрос к сервреру");
	}

	vector<uint32_t> header(2);
	memcpy(&header[0], &raw[0], sizeof(uint32_t) * 2);

	return actions.at(be32toh(header[1]))->process(request, socket);
}
