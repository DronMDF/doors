# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.test import TestCase


class ControllerViewTest(TestCase):
	def testNoControllers(self):
		response = self.client.get('/controller')
		self.assertEqual(response.status_code, 200)
