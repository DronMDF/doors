// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "TestIoService.h"
#include <core/UdpHandler.h>

using namespace std;

TestIoService::TestIoService(const shared_ptr<const Bytes> &response)
	: response(response)
{
}

void TestIoService::async_udp_request(
	const string &address [[gnu::unused]],
	in_port_t port [[gnu::unused]],
	const shared_ptr<const Bytes> &request [[gnu::unused]],
	const shared_ptr<const UdpHandler> &handler
) const
{
	handler->handle(response);
}

void TestIoService::async_http_request(
	const string &uri [[gnu::unused]],
	const string &request [[gnu::unused]],
	const shared_ptr<const StorageHandler> &handler [[gnu::unused]]
) const
{
	throw runtime_error("Not implemented");
}
