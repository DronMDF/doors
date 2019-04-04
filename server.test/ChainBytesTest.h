// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "2out/2out.h"

class ChainBytesTest final : public oout::Test {
public:
	ChainBytesTest();
	std::unique_ptr<const oout::Result> result() const override;
private:
	const std::shared_ptr<const oout::Test> tests;
};

