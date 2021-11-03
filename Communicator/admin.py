from django.contrib import admin

# Register your models here.
from Communicator.models import Event
from Communicator.models.terminal import Terminal

admin.site.register(Terminal)
admin.site.register(Event)

