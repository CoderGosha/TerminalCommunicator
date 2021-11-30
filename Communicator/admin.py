from django.contrib import admin

# Register your models here.
from django.contrib.auth.models import Permission

from Communicator.models import Event
from Communicator.models.terminal import Terminal

from django.contrib import admin


class EventAdmin(admin.ModelAdmin):
    model = Event
    list_per_page = 10  # No of records per page
    list_display = ('event_type', 'terminal', 'data_create', 'data_expired', 'success')
    list_filter = ('terminal',)
    ordering = ('-data_create',)
    search_fields = ('request',)
    pass


class TerminalAdmin(admin.ModelAdmin):
    model = Terminal
    list_per_page = 10  # No of records per page
    list_display = ('name', 'owner', 'is_active', 'last_connect', 'ip_address', 'request_count' )
    # list_filter = ('owner',)
    ordering = ('-last_connect',)
    search_fields = ('name',)

    def request_count(self, obj):
        return f"{obj.count_request}/{obj.count_request_error}"
    pass


admin.site.register(Event, EventAdmin)
admin.site.register(Terminal, TerminalAdmin)
admin.site.register(Permission)

