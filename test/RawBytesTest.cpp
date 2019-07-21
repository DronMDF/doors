// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "RawBytesTest.h"
#include <core/RawBytes.h>
#include "BytesRepr.h"

using namespace std;
using namespace oout;

RawBytesTest::RawBytesTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"RawBytes construct from vector",
				make_shared<TestEqual>(
					make_shared<BytesRepr>(
						make_shared<RawBytes>(
							vector<uint8_t>{5, 6, 7, 8, 9, 10}
						)
					),
					"05060708 090a"
				)
			)
		)
	)
{
}

unique_ptr<const oout::Result> RawBytesTest::result() const
{
	return tests->result();
}
