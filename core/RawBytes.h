// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Bytes.h"

class RawBytes final : public Bytes {
public:
	RawBytes(const void *ptr, size_t size);

	std::vector<uint8_t> raw() const override;
private:
	const std::vector<uint8_t> bytes;
};
