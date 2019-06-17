// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <chrono>
#include <vector>
#include <core/UdpService.h>

class BenchmarkStats final {
public:
	explicit BenchmarkStats(size_t lock_count);
	void time(const std::chrono::high_resolution_clock::duration &time);
private:
	const size_t lock_count;
	std::vector<std::chrono::high_resolution_clock::duration> times;
	std::chrono::high_resolution_clock::time_point first;
	std::chrono::high_resolution_clock::time_point last;

	std::chrono::duration<double> percentil_point(size_t n) const;
};

class BenchmarkUdpService final : public UdpService {
public:
	BenchmarkUdpService(
		const std::shared_ptr<UdpService> &service,
		const std::shared_ptr<BenchmarkStats> &stats
	);

	void request(
		const std::string &address,
		in_port_t port,
		const std::shared_ptr<const Bytes> &request,
		const std::shared_ptr<const UdpHandler> &handler
	) const override;
private:
	const std::shared_ptr<UdpService> service;
	const std::shared_ptr<BenchmarkStats> stats;
};
