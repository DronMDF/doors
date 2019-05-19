// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "LockBytesTest.h"
#include <core/LockBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

LockBytesTest::LockBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"LockBytes representation",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<LockBytes>(7, 0x88, 0x123456789ABCDEF)
					),
					"00000001 00000008 00000007 00000088 01234567 89abcdef "
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> LockBytesTest::result() const
{
	return tests->result();
}

