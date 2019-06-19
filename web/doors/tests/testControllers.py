# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.test import TestCase
from xml.etree import ElementTree
from doors.models import Controller


class ControllersTest(TestCase):
	def testControllersList(self):
		Controller.objects.create(address='19.6.22.56', port='5000')
		response = self.client.get('/controllers/')
		self.assertEqual(response.status_code, 200)
		xml = ElementTree.fromstring(response.content.decode('utf8'))
		self.assertIsNotNone(xml.find(".//controller[address='19.6.22.56']"))

