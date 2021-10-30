import uuid
from django.db import models


class Terminal(models.Model):
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, editable=False)
    name = models.CharField(max_length=50)
    info = models.CharField(max_length=200, blank=True)
    ip_address = models.CharField(max_length=50, blank=True)
    is_active = models.BooleanField(default=False)
    last_connect = models.DateTimeField(null=True, blank=True)
    count_request = models.IntegerField(default=0)
    owner = models.ForeignKey('auth.User', related_name='terminals', on_delete=models.CASCADE,
                              default=1)

    def __str__(self):
        return f'{self.name} ({self.id}) -{self.ip_address or "no connect"}'
