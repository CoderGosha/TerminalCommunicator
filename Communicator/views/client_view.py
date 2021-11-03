from django.shortcuts import render

# Create your views here.
from rest_framework import status
from rest_framework.authentication import TokenAuthentication, SessionAuthentication
from rest_framework.decorators import permission_classes
from rest_framework.generics import GenericAPIView
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework_swagger import renderers

from Communicator.api.serializers import PingSerializer, EventItemSerializer, EventResultSerializer
from Communicator.extensions.http_extensions import visitor_ip_address
from Communicator.models import Event
from Communicator.models.terminal import Terminal


class PingView(APIView):
    authentication_classes = [TokenAuthentication, SessionAuthentication]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        return Response({"Ok"})

    def post(self, request):
        serialazer = PingSerializer(data=request.data)
        ip_address = visitor_ip_address(request)
        if serialazer.is_valid(raise_exception=True):
            ping = Terminal.objects.filter(name=serialazer.validated_data['name']).first()
            if ping is None:
                ping = serialazer.save(owner=self.request.user, ip_address=ip_address)
            else:
                ping = serialazer.update(ping, validated_data=request.data)
                ping.ip_address = ip_address
                ping.save()
            return Response({"success": "Ok"})


class EventView(APIView):
    authentication_classes = [TokenAuthentication, SessionAuthentication]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        name = self.request.query_params.get('name')
        if name is None:
            return Response(f"Invalid name", status.HTTP_400_BAD_REQUEST)
        terminal = Terminal.objects.filter(name=name).filter(owner=self.request.user).first()
        if terminal is None:
            return Response(f"Terminal not found", status.HTTP_404_NOT_FOUND)

        events = Event.objects.filter(terminal__id=terminal.id).filter(success__isnull=True).order_by('data_create').all()
        serializer = EventItemSerializer(events, many=True)
        return Response(serializer.data)

    def post(self, request):
        if "id" not in self.request.data:
            return Response(f"Invalid id", status.HTTP_400_BAD_REQUEST)
        pk = self.request.data["id"]

        event = Event.objects.filter(pk=pk).filter(success__isnull=True).first()
        if event is None:
            return Response("Event not found", status=status.HTTP_404_NOT_FOUND)

        serialazer = EventResultSerializer(event, data=request.data)
        if serialazer.is_valid(raise_exception=True):
            serialazer.save()

            # Увеличим счетчики для терминала)
            event.terminal.count_request += 1
            if not event.success:
                event.terminal.count_request_error += 1
            event.terminal.save()

            return Response({"success": "Ok"})
        return Response(serialazer.errors, status=status.HTTP_400_BAD_REQUEST)


