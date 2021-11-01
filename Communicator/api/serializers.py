from datetime import datetime

from rest_framework import serializers

from Communicator.models import Terminal
from rest_framework.fields import CurrentUserDefault


class PingSerializer(serializers.ModelSerializer):
    # owner = serializers.ReadOnlyField(source='owner.username')

    class Meta:
        model = Terminal
        fields = ['name', 'info']

    def create(self, validated_data):
        return Terminal.objects.create(**validated_data, last_connect=datetime.now())

    def update(self, instance, validated_data):
        # instance.ip_address = validated_data.get('ip_address', instance.ip_address)
        instance.info = validated_data.get('info', instance.info)
        instance.last_connect = datetime.now()
        return instance
