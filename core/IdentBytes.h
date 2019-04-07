// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Bytes.h"

class IdentBytes final : public Bytes {
public:
	IdentBytes(uint32_t id, uint32_t lock_no);
	std::vector<uint8_t> raw() const override;
private:
	const uint32_t id;
	const uint32_t lock_no;
};
