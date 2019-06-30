# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.contrib.staticfiles import finders
from django.test import TestCase
from xml.etree import ElementTree
from doors.models import Controller, Lock


class ControllersTest(TestCase):
	def testControllersXsl(self):
		''' Если файл не будет найден - функция вернет None '''
		xsl_path = finders.find('controllers.xsl')
		self.assertIsInstance(xsl_path, str)

	def testControllersXml(self):
		Controller.objects.create(address='19.6.22.56', port='5000')
		response = self.client.get('/controllers/')
		self.assertEqual(response.status_code, 200)
		xml = ElementTree.fromstring(response.content.decode('utf8'))
		self.assertIsNotNone(xml.find(".//controller[address='19.6.22.56']"))

	def testControllerXsl(self):
		xsl_path = finders.find('controller.xsl')
		self.assertIsInstance(xsl_path, str)

	def testControllerXml(self):
		controller = Controller.objects.create(address='26.6.22.27', port='5000')
		Lock.objects.create(hwid=10, controller=controller)
		Lock.objects.create(hwid=20, controller=controller)
		response = self.client.get('/controllers/%u/' % controller.id)
		self.assertEqual(response.status_code, 200)
		xml = ElementTree.fromstring(response.content.decode('utf8'))
		self.assertIsNotNone(xml.find(".//lock[hwid='10']"))
		self.assertIsNotNone(xml.find(".//lock[hwid='20']"))
