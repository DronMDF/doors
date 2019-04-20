# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.contrib import admin
from .models import Controller


class ControllerAdmin(admin.ModelAdmin):
	list_display = ['address', 'port']

admin.site.register(Controller, ControllerAdmin)
