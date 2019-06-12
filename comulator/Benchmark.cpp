// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "Benchmark.h"
#include <algorithm>
#include <iostream>
#include <fmt/format.h>

using namespace std;

class BenchmarkUdpHandler final : public UdpHandler {
public:
	BenchmarkUdpHandler(
		const shared_ptr<const UdpHandler> &handler,
		const shared_ptr<BenchmarkStats> &stats,
		const chrono::high_resolution_clock::time_point &start
	) : handler(handler), stats(stats), start(start)
	{
	}

	void handle(const shared_ptr<const Bytes> &reply) const override
	{
		const auto end = chrono::high_resolution_clock::now();
		stats->time(end - start);
		handler->handle(reply);
	}

private:
	const shared_ptr<const UdpHandler> handler;
	const shared_ptr<BenchmarkStats> stats;
	const chrono::high_resolution_clock::time_point start;
};

BenchmarkStats::BenchmarkStats(size_t lock_count)
	: lock_count(lock_count)
{
}

void BenchmarkStats::time(const chrono::high_resolution_clock::duration &time)
{
	times.push_back(time);
	if (times.size() >= lock_count) {
		sort(times.begin(), times.end());
		chrono::duration<double> t99 = times[lock_count * 99 / 100];
		cout << fmt::format("99%: {0:.6f}sec", t99.count()) << endl;
		times.clear();
	}
}

BenchmarkUdpService::BenchmarkUdpService(
	const shared_ptr<UdpService> &service,
	const shared_ptr<BenchmarkStats> &stats
) : service(service), stats(stats)
{
}

void BenchmarkUdpService::request(
	const string &address,
	in_port_t port,
	const shared_ptr<const Bytes> &request,
	const shared_ptr<const UdpHandler> &handler
) const
{
	service->request(
		address,
		port,
		request,
		make_shared<BenchmarkUdpHandler>(
			handler,
			stats,
			chrono::high_resolution_clock::now()
		)
	);
}
