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
from django.urls import path, include
from django.views.generic import TemplateView
from rest_framework_swagger.views import get_swagger_view

from rest_framework.schemas import get_schema_view

import Communicator

schema_view = get_swagger_view(title='TerminalCommunicator')


urlpatterns = [
    url(r'^$', TemplateView.as_view(
        template_name='swagger-ui.html',
        extra_context={'schema_url': 'openapi-schema'}
    ), name='openapi-schema'),

    path('openapi/', get_schema_view(
        title="TerminalCommunicator",
        description="API",
        version="0.0.1"
    ), name='openapi-schema'),
    path('api/', include('Communicator.urls')),
    path('admin/', admin.site.urls),
    # url(r'^$', schema_view),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework')),
]
