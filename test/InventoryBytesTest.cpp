// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryBytesTest.h"
#include <core/InventoryBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

InventoryBytesTest::InventoryBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"InventoryBytes returns valid",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<InventoryBytes>(10)
					),
					"00000001 00000004 0000000a "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> InventoryBytesTest::result() const
{
	return tests->result();
}
