// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "List64BytesTest.h"
#include <core/List64Bytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

List64BytesTest::List64BytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"List64Bytes keep data in be",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<List64Bytes>(
							vector<uint64_t>{7, 8}
						)
					),
					"00000002 00000000 00000007 00000000 00000008 "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> List64BytesTest::result() const
{
	return tests->result();
}
