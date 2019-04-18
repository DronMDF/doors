"""web URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from doors.views import ControllerView

urlpatterns = [
    path('controller/', ControllerView.as_view()),
    # @todo #72 Создать точку входа для обновления в контроллере списка замков
    #  PUT /controller/address:port/locks
    #  Эта точка принимает список замков, и обновляет содержимое базы.
    #  Возможно стоит сделать замки не стираемыми, а отключаемыми. Замок типа исчез.
    path('admin/', admin.site.urls),
]
