// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <chrono>
#include "Scheduler.h"
#include "Storage.h"

// Декоратор RetryStorage обеспечивает гарантированную доставку
// информации из хранилища. Если в хранилище происходит сбой,
// через указанный интервал произойдет повторная попытка обращения к хранилищу.
// Это пока никак не ограничивается
class RetryStorage final : public Storage {
public:
	RetryStorage(
		const std::shared_ptr<Storage> &storage,
		const std::shared_ptr<Scheduler> &scheduler,
		const std::chrono::steady_clock::duration &interval
	);

	void query(
		const std::string &query,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;

	void update(const std::string &query, const nlohmann::json &data) override;
private:
	const std::shared_ptr<Storage> storage;
	const std::shared_ptr<Scheduler> scheduler;
	const std::chrono::steady_clock::duration interval;
};
