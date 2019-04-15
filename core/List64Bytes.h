// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Bytes.h"

class List64Bytes final : public Bytes {
public:
	explicit List64Bytes(const std::vector<uint64_t> &values);
	std::vector<uint8_t> raw() const override;
private:
	const std::vector<uint64_t> values;
};