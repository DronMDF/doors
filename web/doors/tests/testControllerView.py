# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.test import TestCase
from doors.models import Controller, Lock
import json


class ControllerViewTest(TestCase):
	def testNoControllers(self):
		response = self.client.get('/controller/')
		self.assertEqual(response.status_code, 200)

	def testConcreteController(self):
		Controller.objects.create(address='3.2.3.2', port='7777')
		response = self.client.get('/controller/')
		self.assertEqual(response.status_code, 200)
		rep = json.loads(response.content.decode('utf8'))
		self.assertEqual(rep['controllers'][0]['address'], '3.2.3.2')
		self.assertEqual(rep['controllers'][0]['port'], 7777)

	def testControllerLocksUpdate(self):
		controller = Controller.objects.create(address='3.2.3.2', port='7777')
		self.client.post(
			'/controller/%u/locks' % controller.id,
			{"locks": [18, 15, 12]},
			content_type='application/json'
		)
		locks = Lock.objects.filter(controller=controller)
		self.assertListEqual(sorted(l.hwid for l in locks), [12, 15, 18])

	def testControllerLockUpdateWithoutDoubles(self):
		controller = Controller.objects.create(address='3.2.3.2', port='7777')
		self.client.post(
			'/controller/%u/locks' % controller.id,
			{"locks": [18]},
			content_type='application/json'
		)
		self.client.post(
			'/controller/%u/locks' % controller.id,
			{"locks": [18]},
			content_type='application/json'
		)
		locks = Lock.objects.filter(controller=controller)
		self.assertListEqual(sorted(l.hwid for l in locks), [18])

	def testControllerQueryLock(self):
		controller = Controller.objects.create(address='3.2.3.2', port='7777')
		lock = Lock.objects.create(hwid=3, controller=controller)
		response = self.client.get(
			'/controller/%u/lock/%u/lock?key=123456789'
			% (controller.id, lock.id)
		)
		self.assertEqual(response.status_code, 200)
		rep = json.loads(response.content.decode('utf8'))
		self.assertTrue(rep['approve'])

	def testControllerQueryUnlock(self):
		controller = Controller.objects.create(address='3.2.3.2', port='7777')
		lock = Lock.objects.create(hwid=3, controller=controller)
		response = self.client.get(
			'/controller/%u/lock/%u/unlock?key=123456789'
			% (controller.id, lock.id)
		)
		self.assertEqual(response.status_code, 200)
		rep = json.loads(response.content.decode('utf8'))
		self.assertTrue(rep['approve'])
