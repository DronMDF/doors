# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.test import TestCase
from doors.models import Controller


class ControllerViewTest(TestCase):
	def testNoControllers(self):
		response = self.client.get('/controller/')
		self.assertEqual(response.status_code, 200)
		self.assertIn('<?xml', response.content.decode('utf8'))

	def testConcreteController(self):
		Controller.objects.create(address='3.2.3.2', port='7777')
		response = self.client.get('/controller/')
		self.assertEqual(response.status_code, 200)
		self.assertIn('address>3.2.3.2</address', response.content.decode('utf8'))
		self.assertIn('port>7777</port', response.content.decode('utf8'))
