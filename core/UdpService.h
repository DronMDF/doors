// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <string>
#include <netinet/in.h>

class Bytes;

class UdpHandler {
public:
	virtual ~UdpHandler() = default;

	virtual void handle(const std::shared_ptr<const Bytes> &reply) const = 0;
};

// @todo #116 Операции ввода-вывода можно трассировать написав декоратор на IoService
//  И на Storage тоже...
class UdpService {
public:
	virtual ~UdpService() = default;

	virtual void request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const = 0;
};
