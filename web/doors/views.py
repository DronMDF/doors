# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.http import JsonResponse
from django.views import generic, View
from django.views.generic.detail import SingleObjectMixin
import json
from .models import Controller, Lock


class ControllersView(generic.ListView):
	model = Controller
	content_type = 'text/json'
	template_name = 'controllers.json'


class ControllersLockView(SingleObjectMixin, View):
	model = Controller
	def post(self, request, **kwargs):
		self.object = self.get_object()
		locks = json.loads(request.body.decode('utf8')).get('locks')
		# @todo #92 Нужно сравнивать списки замков с имеющимися
		#  И добавлять только если замок новый
		for l in locks:
			Lock.objects.create(controller=self.object, hwid=l)
		return JsonResponse({})

