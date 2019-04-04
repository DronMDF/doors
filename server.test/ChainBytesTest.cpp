// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ChainBytesTest.h"
#include <core/ChainBytes.h>
#include <core/InventoryBytes.h>
#include <core/List32Bytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

ChainBytesTest::ChainBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"ChainBytes join two Bytes",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<ChainBytes>(
							make_shared<InventoryBytes>(10),
							make_shared<List32Bytes>(
								vector<uint32_t>{1, 2}
							)
						)
					),
					"00000001 00000004 0000000a 00000002 00000001 00000002 "
				)
			)
		)
	)
{
}


unique_ptr<const oout::Result> ChainBytesTest::result() const
{
	return tests->result();
}


