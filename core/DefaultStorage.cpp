// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "DefaultStorage.h"

using namespace std;

class DefaultStorageHandler final : public StorageHandler {
public:
	DefaultStorageHandler(
		const shared_ptr<const StorageHandler> &handler,
		const nlohmann::json &data
	) : handler(handler), data(data)
	{
	}

	void handle(const nlohmann::json &result) const override
	{
		auto rv = data;
		rv.merge_patch(result);
		handler->handle(rv);
	}
private:
	const shared_ptr<const StorageHandler> handler;
	const nlohmann::json data;
};

DefaultStorage::DefaultStorage(const shared_ptr<Storage> &storage, const nlohmann::json &data)
	: storage(storage), data(data)
{
}

nlohmann::json DefaultStorage::query(const string &query) const
{
	try {
		const auto result = storage->query(query);
		auto rv = data;
		rv.merge_patch(result);
		return rv;
	} catch (const std::exception &) {
		// @todo #38 Необходимо обеспечить возможность протоколирования.
		//  Здесь какраз подходящее место, чтобы записать строчку в лог
		return data;
	}
}

void DefaultStorage::async_query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	storage->async_query(
		query,
		make_shared<DefaultStorageHandler>(handler, data)
	);
}

void DefaultStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
	throw runtime_error("Некорректное использование DefaultStorage");
}
