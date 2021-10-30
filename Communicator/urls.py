from django.conf.urls import url
from django.urls import path
from rest_framework.schemas import get_schema_view
from rest_framework_swagger.renderers import SwaggerUIRenderer, OpenAPIRenderer

from Communicator.views import PingView

app_name = "Communicator"

schema_view = get_schema_view(title='Users API', renderer_classes=[OpenAPIRenderer, SwaggerUIRenderer])


# app_name will help us do a reverse look-up latter.
urlpatterns = [

]