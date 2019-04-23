// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#include "InventoryReqBytes.h"
#include <cstring>
#include <protocol.h>

using namespace std;

vector<uint8_t> InventoryReqBytes::raw() const
{
	InventoryReq req;
	vector<uint8_t> rv(sizeof(req));
	memcpy(&rv[0], &req, sizeof(req));
	return rv;
}
