// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <cstdint>
#include <vector>

class Bytes {
public:
	virtual ~Bytes() = default;
	virtual std::vector<uint8_t> raw() const = 0;
};
