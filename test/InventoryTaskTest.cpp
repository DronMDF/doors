// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryTaskTest.h"
#include <core/ChainBytes.h>
#include <core/InventoryBytes.h>
#include <core/List32Bytes.h>
#include <core/InventoryTask.h>
#include "LogStorage.h"
#include "TestUdpService.h"

using namespace std;
using namespace oout;


class InventoryUpdateRepr final : public oout::Representation {
public:
	explicit InventoryUpdateRepr(const shared_ptr<UdpService> &service)
		: service(service)
	{
	}

	string asString() const
	{
		auto storage = make_shared<LogStorage>();
		InventoryTask(10, "1.1.1.1", 1234, storage, service, {}, 0).run();
		return storage->asString();
	}
private:
	const shared_ptr<UdpService> service;
};

InventoryTaskTest::InventoryTaskTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"InventoryTask update controller by id",
				make_shared<TestStartsWith>(
					make_shared<InventoryUpdateRepr>(
						make_shared<TestUdpService>(
							make_shared<ChainBytes>(
								make_shared<InventoryBytes>(10),
								make_shared<List32Bytes>()
							)
						)
					),
					"/controller/10/locks"
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> InventoryTaskTest::result() const
{
	return tests->result();
}

