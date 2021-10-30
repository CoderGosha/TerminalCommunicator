"""TerminalCommunicator URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
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
from django.conf.urls import url
from django.contrib import admin
from django.urls import path
from django.views.generic import TemplateView
from rest_framework import schemas, permissions
from rest_framework.schemas import get_schema_view, openapi
from rest_framework_swagger.renderers import SwaggerUIRenderer, OpenAPIRenderer

from Communicator.api.views.ApiView import ApiView
from Communicator.views import PingView

app_name = "Communicator"

from rest_framework.schemas import get_schema_view

from rest_framework.renderers import CoreJSONRenderer


urlpatterns = [
    path('swagger-ui/', TemplateView.as_view(
        template_name='swagger-ui.html',
        extra_context={'schema_url': 'openapi-schema'}
    ), name='swagger-ui'),
    path('swagger/', ApiView.as_view()),
    path('ping/', PingView.as_view()),
    path('admin/', admin.site.urls),
]
