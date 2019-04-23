// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "ConfigBytesTest.h"
#include <core/ConfigBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

ConfigBytesTest::ConfigBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"ConfigBytes returns valid",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<ConfigBytes>(7, 0x33, 0x666, 3)
					),
					"00000001 00000005 00000007 00000033 00000666 00000003 "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> ConfigBytesTest::result() const
{
	return tests->result();
}
