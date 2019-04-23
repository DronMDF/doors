// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "IoService.h"
#include <asio/ts/internet.hpp>

class NetIoService final : public IoService {
public:
	explicit NetIoService(asio::io_context *context);
	void async_udp_request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const override;

private:
	asio::io_context *context;
};
