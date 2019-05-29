// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "PredefinedStorage.h"

using namespace std;

// @todo #101 Вместо PredefinedStorageResponse класса
//  можно было бы использовать JsonStorageResponse, если бы у нас такой был.
class PredefinedStorageResponse final : public StorageResponse {
public:
	explicit PredefinedStorageResponse(const nlohmann::json &data)
		: data(data)
	{
	}

	nlohmann::json json() const override
	{
		return data;
	}
private:
	const nlohmann::json data;
};

PredefinedStorage::PredefinedStorage(const map<string, nlohmann::json> &info)
	: info(info)
{
}

PredefinedStorage::PredefinedStorage(const string &query, const nlohmann::json &result)
	: PredefinedStorage({make_pair(query, result)})
{
}

void PredefinedStorage::query(
	const string &query,
	const shared_ptr<const StorageHandler> &handler
) const
{
	handler->handle(make_shared<PredefinedStorageResponse>(info.at(query)));
}

void PredefinedStorage::update(
	const string &query [[gnu::unused]],
	const nlohmann::json &data [[gnu::unused]]
)
{
}
