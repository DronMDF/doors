// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "StatusActionTest.h"
#include <protocol.h>
#include <2out/2out.h>
#include <server.core/ImmediatlyScheduler.h>
#include <server.core/StatusAction.h>
#include "ActionRepr.h"
#include "TestStorage.h"

using namespace std;
using namespace oout;

StatusActionTest::StatusActionTest()
	: tests(
		make_shared<TestNamed>(
			"StatusActionTest return nothing",
			make_shared<TestEqual>(
				make_shared<ActionRepr>(
					make_shared<StatusAction>(
						make_shared<TestStorage>(
							"/status/0000000000000001",
							nlohmann::json(
								{"balance", 0x777}
							)
						),
						make_shared<ImmediatlyScheduler>()
					),
					vector<uint32_t>{
						1, KEY_STATUS_REQ, 0,
						0, 1
					}
				),
				"00000001 "
				"00000007 "
				"00000000 "
				"00000000 00000001 "
				"00000000 00000000 "
				"ffffffff "
				"00000777 "
				"00000000 "
			)
		)
	)
{
}


unique_ptr<const oout::Result> StatusActionTest::result() const
{
	return tests->result();
}
