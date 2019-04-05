// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <cstdint>
#include <vector>

class BytesInventory final {
public:
	explicit BytesInventory(const std::vector<uint8_t> &bytes);
	BytesInventory(const void *ptr, size_t size);

	std::vector<uint32_t> locks() const;
private:
	const std::vector<uint8_t> bytes;
};
