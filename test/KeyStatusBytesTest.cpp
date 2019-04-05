// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "KeyStatusBytesTest.h"
#include <core/KeyStatusBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

KeyStatusBytesTest::KeyStatusBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"KeyStatusBytes result",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<KeyStatusBytes>(
							0x88, 0x5ec, 0x111, 0x12345678, 0x777
						)
					),
					"00000001 00000007 00000088 "
					"00000000 000005ec "
					"00000000 00000111 "
					"12345678 "
					"00000777 "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> KeyStatusBytesTest::result() const
{
	return tests->result();
}
