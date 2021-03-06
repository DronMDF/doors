// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <core/UdpService.h>

class TestUdpService final : public UdpService {
public:
	explicit TestUdpService(const std::shared_ptr<const Bytes> &response);

	void request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const override;
private:
	const std::shared_ptr<const Bytes> response;
};
