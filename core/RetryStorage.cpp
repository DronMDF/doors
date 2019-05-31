// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "RetryStorage.h"
#include "Task.h"

using namespace std;

class RetryStorageTask final : public Task {
public:
	RetryStorageTask(
		const shared_ptr<Storage> &storage,
		const string &query,
		const shared_ptr<const StorageHandler> &handler,
		const shared_ptr<Scheduler> &scheduler,
		const chrono::steady_clock::duration &interval
	) : storage(storage),
	    query(query),
	    handler(handler),
	    scheduler(scheduler),
	    interval(interval)
	{
	}

	void run() const override
	{
		RetryStorage(storage, scheduler, interval).query(query, handler);
	}

private:
	const shared_ptr<Storage> storage;
	const string query;
	const shared_ptr<const StorageHandler> handler;
	const shared_ptr<Scheduler> scheduler;
	const chrono::steady_clock::duration interval;
};

class RetryStorageResponse final : public StorageResponse {
public:
	RetryStorageResponse(
		const shared_ptr<const StorageResponse> &response,
		const shared_ptr<Scheduler> &scheduler,
		const shared_ptr<Task> &task,
		const chrono::steady_clock::duration &interval
	) : response(response), scheduler(scheduler), task(task), interval(interval)
	{
	}

	nlohmann::json json() const override
	{
		try {
			return response->json();
		} catch (const exception &e) {
			scheduler->schedule(task, interval);
			throw;
		}
	}

private:
	const shared_ptr<const StorageResponse> response;
	const shared_ptr<Scheduler> scheduler;
	const shared_ptr<Task> task;
	const chrono::steady_clock::duration interval;
};

class RetryStorageHandler final : public StorageHandler {
public:
	RetryStorageHandler(
		const shared_ptr<const StorageHandler> &handler,
		const shared_ptr<Scheduler> &scheduler,
		const shared_ptr<Task> &task,
		const chrono::steady_clock::duration &interval
	) : handler(handler), scheduler(scheduler), task(task), interval(interval)
	{
	}

	void handle(const shared_ptr<const StorageResponse> &response) const
	{
		handler->handle(
			make_shared<RetryStorageResponse>(response, scheduler, task, interval)
		);
	}
private:
	const shared_ptr<const StorageHandler> handler;
	const shared_ptr<Scheduler> scheduler;
	const shared_ptr<Task> task;
	const chrono::steady_clock::duration interval;
};

RetryStorage::RetryStorage(
	const shared_ptr<Storage> &storage,
	const shared_ptr<Scheduler> &scheduler,
	const chrono::steady_clock::duration &interval
) : storage(storage), scheduler(scheduler), interval(interval)
{
}

void RetryStorage::query(const string &query, const shared_ptr<const StorageHandler> &handler) const
{
	storage->query(
		query,
		make_shared<RetryStorageHandler>(
			handler,
			scheduler,
			make_shared<RetryStorageTask>(
				storage,
				query,
				handler,
				scheduler,
				interval
			),
			interval
		)
	);
}

void RetryStorage::update(const string &query, const nlohmann::json &data)
{
	storage->update(query, data);
}
