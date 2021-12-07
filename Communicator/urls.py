from django.urls import path

from Communicator.views import PingView, TokenView, EventView, ProviderView

app_name = "Communicator"

# app_name will help us do a reverse look-up latter.
urlpatterns = [
    path('ping/', PingView.as_view()),
    path('token/', TokenView.as_view()),
    path('event/', EventView.as_view()),
    path('provider/', ProviderView.as_view()),
]
