# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.contrib.staticfiles import finders
from django.test import TestCase
from xml.etree import ElementTree
from doors.models import Controller, Lock


class LocksTest(TestCase):
	def testLockXsl(self):
		xsl_path = finders.find('lock.xsl')
		self.assertIsInstance(xsl_path, str)

	def testLockXml(self):
		controller = Controller.objects.create(address='30.6.23.27', port='5000')
		lock = Lock.objects.create(hwid=20, controller=controller)
		response = self.client.get('/locks/%u/' % lock.id)
		self.assertEqual(response.status_code, 200)
		xml = ElementTree.fromstring(response.content.decode('utf8'))
		self.assertEqual(xml.tag, 'lock')
		self.assertEqual(xml.attrib['id'], str(lock.id))
		self.assertEqual(xml.find("./hwid").text, '20')
