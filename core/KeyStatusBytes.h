// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Bytes.h"

class KeyStatusBytes final : public Bytes {
public:
	KeyStatusBytes(
		uint32_t id,
		uint64_t key,
		uint64_t contract,
		uint32_t expired,
		int32_t money
	);
	std::vector<uint8_t> raw() const override;
private:
	const uint32_t id;
	const uint64_t key;
	const uint64_t contract;
	const uint32_t expired;
	const int32_t money;
};
