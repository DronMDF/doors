// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <string>
#include <netinet/in.h>

class Bytes;
class UdpHandler;

class IoService {
public:
	virtual ~IoService() = default;

	virtual void async_udp_request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const = 0;
};
