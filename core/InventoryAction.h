// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "Action.h"

class Storage;

// Этот класс используется из comulator, и ему не нужен планировщик
class InventoryAction final : public Action {
public:
	explicit InventoryAction(const std::shared_ptr<Storage> &storage);

	bool process(
		const std::vector<uint8_t> &request,
		const std::shared_ptr<Socket> &socket
	) const override;

private:
	const std::shared_ptr<Storage> storage;
};
