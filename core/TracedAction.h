// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Action.h"

// Этот класс осуществляет протоколирование происходящих событий
class TracedAction final : public Action {
public:
	TracedAction(const std::string &tag, const std::shared_ptr<const Action> &action);

	bool process(
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<Socket> &socket
	) const override;

private:
	const std::string tag;
	const std::shared_ptr<const Action> action;
};
