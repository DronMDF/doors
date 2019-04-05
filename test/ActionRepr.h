// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <memory>
#include <2out/2out.h>
#include <core/Action.h>

class ActionRepr final : public oout::Representation {
public:
	ActionRepr(
		const std::shared_ptr<const Action> &action,
		const std::vector<uint32_t> &request
	);

	std::string asString() const override;
private:
	const std::shared_ptr<const Action> action;
	const std::vector<uint32_t> request;
};
