// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LogIoService.h"
#include <fmt/format.h>
#include <core/Bytes.h>

using namespace std;

void LogIoService::async_udp_request(
	const string &address,
	in_port_t port,
	const shared_ptr<const Bytes> &request,
	const shared_ptr<const UdpHandler> &handler
) const
{
	log += fmt::format("{0}:{1} ", address, port);
	for (const auto &b : request->raw()) {
		log += fmt::format("{0:02x} ", b);
	}
	log += "\n";
}

string LogIoService::asString() const
{
	return log;
}
