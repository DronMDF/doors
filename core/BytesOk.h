// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

class BytesOk final {
public:
	explicit BytesOk(const std::vector<uint8_t> &bytes);
	BytesOk(const void *ptr, size_t size);

	uint32_t opt() const;
private:
	const std::vector<uint8_t> bytes;
};
