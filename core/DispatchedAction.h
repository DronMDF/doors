// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <map>
#include "Action.h"

class DispatchedAction final : public Action {
public:
	explicit DispatchedAction(const std::map<uint32_t, std::shared_ptr<Action>> &actions);

	template<typename ... T>
	DispatchedAction(const std::pair<uint32_t, std::shared_ptr<Action>> &action, T ... args)
		: DispatchedAction(std::map<uint32_t, std::shared_ptr<Action>>{action, args...})
	{
	}

	template<typename ... T>
	DispatchedAction(uint32_t code, const std::shared_ptr<Action> &action, T ... args)
		: DispatchedAction(args..., std::make_pair(code, action))
	{
	}

	void process(
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<Socket> &socket
	) const override;

private:
	const std::map<uint32_t, std::shared_ptr<Action>> actions;
};
