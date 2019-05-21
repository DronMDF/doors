// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <cstdint>
#include <vector>

class BytesUnlock final {
public:
	explicit BytesUnlock(const std::vector<uint8_t> &bytes);

	uint32_t id() const;
private:
	const std::vector<uint8_t> bytes;
};
