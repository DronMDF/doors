// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "DispatchedActionTest.h"
#include <core/DispatchedAction.h>
#include "ActionRepr.h"
#include "TestAction.h"

using namespace std;
using namespace oout;

DispatchedActionTest::DispatchedActionTest()
	: tests(
		make_shared<TestSuite>(
			make_shared<TestNamed>(
				"DispatchedAction select right entry",
				make_shared<TestEqual>(
					make_shared<ActionRepr>(
						make_shared<DispatchedAction>(
							1, make_shared<TestAction>(0x11111111),
							2, make_shared<TestAction>(0x22222222)
						),
						vector<uint32_t>{1, 2, 0, 0, 1}
					),
					"22222222 "
				)
			)
		)
	)
{
}


unique_ptr<const oout::Result> DispatchedActionTest::result() const
{
	return tests->result();
}
