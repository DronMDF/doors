// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include "Bytes.h"

class ChainBytes final : public Bytes {
public:
	ChainBytes(const std::shared_ptr<const Bytes> &a, const std::shared_ptr<const Bytes> &b);
	std::vector<uint8_t> raw() const override;
private:
	const std::shared_ptr<const Bytes> a;
	const std::shared_ptr<const Bytes> b;
};
