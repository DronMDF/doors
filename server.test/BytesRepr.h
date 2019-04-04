// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <2out/2out.h>

class Bytes;

class BytesRepr final : public oout::Representation {
public:
	explicit BytesRepr(const std::shared_ptr<const Bytes> &bytes);

	std::string asString() const override;
private:
	const std::shared_ptr<const Bytes> bytes;
};
