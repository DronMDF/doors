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
from doors.views import *

urlpatterns = [
    path('controller/', ControllersView.as_view()),
    path('controller/<int:pk>/locks', controller_locks_update),
    path('controller/<int:pk>/lock/<int:lk>/lock', controller_query_lock),
    path('controller/<int:pk>/lock/<int:lk>/unlock', controller_query_unlock),
    path('admin/', admin.site.urls),
]
