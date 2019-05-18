// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once

class Bytes;

class UdpHandler {
public:
	virtual ~UdpHandler() = default;

	virtual void handle(const std::shared_ptr<const Bytes> &reply) const = 0;
};
