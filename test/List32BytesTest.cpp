// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "List32BytesTest.h"
#include <core/List32Bytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

List32BytesTest::List32BytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"List32Bytes keep data in be",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<List32Bytes>(
							vector<uint32_t>{7, 8, 9}
						)
					),
					"00000003 00000007 00000008 00000009 "
				)
			)
		)
	)
{
}


unique_ptr<const oout::Result> List32BytesTest::result() const
{
	return tests->result();
}
