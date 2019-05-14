# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.http import JsonResponse
from django.views import generic
from django.views.decorators.csrf import csrf_exempt
import json
from .models import Controller, Lock


class ControllersView(generic.ListView):
	model = Controller
	content_type = 'text/json'
	template_name = 'controllers.json'


@csrf_exempt
def controller_locks_update(request, pk):
	controller = Controller.objects.get(pk=pk)
	old_locks = {l.hwid for l in Lock.objects.filter(controller=controller)}
	Lock.objects.bulk_create(
		Lock(controller=controller, hwid=l)
		for l in json.loads(request.body.decode('utf8')).get('locks')
		if l not in old_locks
	)
	return JsonResponse({})

