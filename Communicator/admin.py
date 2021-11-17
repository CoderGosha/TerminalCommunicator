from django.contrib import admin

# Register your models here.
from django.contrib.auth.models import Permission

from Communicator.models import Event
from Communicator.models.terminal import Terminal

admin.site.register(Terminal)
admin.site.register(Event)
admin.site.register(Permission)

