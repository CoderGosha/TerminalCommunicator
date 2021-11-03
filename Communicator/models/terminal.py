import uuid

from django.db import models


class Terminal(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    name = models.CharField(max_length=50)
    display_name = models.CharField(max_length=50, blank=True, null=True)
    info = models.CharField(max_length=200, blank=True)
    ip_address = models.CharField(max_length=50, blank=True)
    is_active = models.BooleanField(default=False)
    last_connect = models.DateTimeField(null=True, blank=True)
    owner = models.ForeignKey('auth.User', related_name='terminals', on_delete=models.CASCADE,
                              default=1)
    metric = models.IntegerField(default=0)
    count_request = models.IntegerField(default=0)
    count_request_error = models.IntegerField(default=0)

    def get_name(self) -> str:
        return self.display_name or self.name

    def __str__(self):
        return f'{self.get_name()} ({self.owner.username}) - {self.last_connect or "no connect"}'
