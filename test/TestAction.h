// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <core/Action.h>

class TestAction final : public Action {
public:
	explicit TestAction(const std::vector<uint32_t> &reply);

	template<typename ... T>
	TestAction(uint32_t arg, T ... args)
		: TestAction(std::vector<uint32_t>{arg, args...})
	{
	}

	void process(
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<Socket> &socket
	) const override;
private:
	const std::vector<uint32_t> reply;
};
