from rest_framework import serializers

from Communicator.models import Terminal


class PingSerializer(serializers.ModelSerializer):
    owner = serializers.ReadOnlyField(source='owner.username')

    class Meta:
        model = Terminal
        fields = ['name', 'info', 'ip_address']

    def create(self, validated_data):
        return Terminal.objects.create(**validated_data)