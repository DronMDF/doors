// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryActionTest.h"
#include <protocol.h>
#include <core/InventoryAction.h>
#include <core/NullStorage.h>
#include "ActionRepr.h"

using namespace std;
using namespace oout;

InventoryActionTest::InventoryActionTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"InventoryAction return INVENTORY",
				make_shared<TestEqual>(
					make_shared<ActionRepr>(
						make_shared<InventoryAction>(
							make_shared<NullStorage>()
						),
						vector<uint32_t>{1, INVENTORY_REQ, 0}
					),
					"00000001 "
					"00000004 "
					"00000000 "
					"00000000 "
				)
			)
		)
	)
{
}


unique_ptr<const oout::Result> InventoryActionTest::result() const
{
	return tests->result();
}
