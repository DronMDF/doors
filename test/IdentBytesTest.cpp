// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "IdentBytesTest.h"
#include <core/IdentBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

IdentBytesTest::IdentBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"IdentBytes returns valid",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<IdentBytes>(0x777, 0x1234)
					),
					"00000001 0000000c 00000777 00001234 "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> IdentBytesTest::result() const
{
	return tests->result();
}
