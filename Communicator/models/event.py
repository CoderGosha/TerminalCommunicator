import uuid
from datetime import datetime
from enum import Enum

from django.db import models

from Communicator.models import Terminal


class Event(models.Model):
    class EventType(models.IntegerChoices):
        EXEC = 0,
        HTTP_GET = 1

    class Meta(object):
        ordering = ['-data_create']

    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    data_create = models.DateTimeField(default=datetime.now())
    event_type = models.IntegerField(
        choices=EventType.choices,
        default=EventType.EXEC,
    )
    request = models.CharField(max_length=100)
    terminal = models.ForeignKey(Terminal, on_delete=models.SET_NULL, blank=True, null=True)

    # Ответ от терминала
    data_completed = models.DateTimeField(blank=True, null=True)
    success = models.BooleanField(blank=True, null=True)
    response = models.TextField(blank=True, null=True)

    def get_status_display(self) -> str:
        if self.success is None:
            return "NOT RUNNING"
        elif self.success:
            return "SUCCESS"
        else:
            return "ERROR"

    def __str__(self):
        return f'{self.get_event_type_display()} ({self.terminal.get_name()}) - {self.data_create}  - {self.get_status_display()}'
