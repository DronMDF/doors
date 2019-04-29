// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <core/IoService.h>

class LogIoService final : public IoService {
public:
	void async_udp_request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const override;

	void async_http_request(
		const std::string &uri,
		const std::string &request,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;

	std::string asString() const;
private:
	mutable std::string log;
};