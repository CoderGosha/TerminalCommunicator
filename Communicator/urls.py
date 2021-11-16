from django.conf.urls import url
from django.urls import path
from django.views.generic import TemplateView
from rest_framework.schemas import get_schema_view
from rest_framework_swagger.renderers import SwaggerUIRenderer, OpenAPIRenderer

from Communicator.views import PingView, TokenView, EventView, ProviderView

app_name = "Communicator"

# app_name will help us do a reverse look-up latter.
urlpatterns = [
    path('ping/', PingView.as_view()),
    path('token/', TokenView.as_view()),
    path('event/', EventView.as_view()),
    path('provider/', ProviderView.as_view()),
]
