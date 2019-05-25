// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include "HttpService.h"
#include <asio/ts/internet.hpp>

class AsioHttpService final : public HttpService {
public:
	explicit AsioHttpService(asio::io_context *context);

	void request(
		const std::string &uri,
		const std::string &request,
		const std::shared_ptr<const StorageHandler> &handler
	) const override;
private:
	asio::io_context *context;
};
