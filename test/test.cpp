// Copyright (c) 2019 Andrey Valyaev
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include <iostream>
#include <2out/2out.h>
#include "BootstrapTaskTest.h"
#include "ConfigBytesTest.h"
#include "ChainBytesTest.h"
#include "DispatchedActionTest.h"
#include "IdentBytesTest.h"
#include "InventoryActionTest.h"
#include "InventoryBytesTest.h"
#include "InventoryTaskTest.h"
#include "KeyStatusBytesTest.h"
#include "List32BytesTest.h"
#include "List64BytesTest.h"
#include "LockBytesTest.h"
#include "RawBytesTest.h"
#include "StatusActionTest.h"

using namespace std;
using namespace oout;

int main(int, char **)
{
	const shared_ptr<const Result> result = TestTimed(
		make_shared<oout::TestSuite>(
			make_shared<BootstrapTaskTest>(),
			make_shared<ConfigBytesTest>(),
			make_shared<ChainBytesTest>(),
			make_shared<DispatchedActionTest>(),
			make_shared<IdentBytesTest>(),
			make_shared<InventoryActionTest>(),
			make_shared<InventoryBytesTest>(),
			make_shared<InventoryTaskTest>(),
			make_shared<KeyStatusBytesTest>(),
			make_shared<List32BytesTest>(),
			make_shared<List64BytesTest>(),
			make_shared<LockBytesTest>(),
			make_shared<RawBytesTest>(),
			make_shared<StatusActionTest>()
		)
	).result();

	cout << JUnitXmlReport(result).asString() << endl;

	return (
		CountFailure(result).count() == 0 &&
		CountError(result).count() == 0
	) ? 0 : -1;
}
