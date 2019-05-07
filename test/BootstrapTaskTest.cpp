// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "BootstrapTaskTest.h"
#include <core/BootstrapTask.h>
#include <core/ImmediatlyScheduler.h>
#include "LogIoService.h"
#include "TestStorage.h"

using namespace std;
using namespace oout;


class BootstrapUdpRepr final : public oout::Representation {
public:
	explicit BootstrapUdpRepr(const shared_ptr<Storage> &storage)
		: storage(storage)
	{
	}

	string asString() const
	{
		auto service = make_shared<LogIoService>();
		BootstrapTask(storage, make_shared<ImmediatlyScheduler>(), service).run();
		return service->asString();
	}
private:
	const shared_ptr<Storage> storage;
};

BootstrapTaskTest::BootstrapTaskTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"BootstrapTask inventory controllers",
				make_shared<TestStartsWith>(
					make_shared<BootstrapUdpRepr>(
						make_shared<TestStorage>(
							"/controller/",
							R"({
								"controllers": [{
								        "id": 15,
									"address": "127.0.0.1",
									"port": 5000
								}]
							})"_json
						)
					),
					"127.0.0.1:5000 00 00 00 01 00 00 00 03"
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> BootstrapTaskTest::result() const
{
	return tests->result();
}
