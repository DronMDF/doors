# Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE file for details.

from django.db import models


class Controller(models.Model):
	address = models.GenericIPAddressField()
	port = models.IntegerField()
	# @todo #92 Добавить контроллеру идентификатор
	#  Который вовсе не обязательно совпадает с pk.

class Lock(models.Model):
	controller = models.ForeignKey(Controller, on_delete=models.CASCADE)
	hwid = models.IntegerField()
	open = models.BooleanField(default=True)
