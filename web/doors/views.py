# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.shortcuts import render
from django.views import generic
from .models import Controller

class ControllerView(generic.ListView):
	model = Controller
	template = 'doors/controller.xml'
