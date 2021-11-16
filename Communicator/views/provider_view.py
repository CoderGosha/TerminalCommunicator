import datetime

from rest_framework import status
from rest_framework.authentication import TokenAuthentication, SessionAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.views import APIView

from Communicator.api.serializers import EventRequestSerializer, EventResultSerializer
from Communicator.models import Terminal, Event


class ProviderView(APIView):
    authentication_classes = [TokenAuthentication, SessionAuthentication]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        id = self.request.query_params.get('id')
        if id is None:
            return Response(f"Invalid id", status.HTTP_400_BAD_REQUEST)
        event = Event.objects.filter(owner=self.request.user).filter(id=id).first()
        serializer = EventResultSerializer(event)
        return Response(serializer.data)

    def post(self, request):
        serialazer = EventRequestSerializer(data=request.data)
        if serialazer.is_valid(raise_exception=True):
            terminal = self.get_terminal()
            if terminal is None:
                return Response({'status': 'terminal not found'}, status=status.HTTP_404_NOT_FOUND)

            event = serialazer.save(owner=self.request.user, terminal=terminal)
            return Response({"success": "Ok", "id": event.id})

    '''
        Выберем все активные терминалы и отсортируем по метрике (добавить ротацию)
    '''
    def get_terminal(self) -> Terminal:
        timeout = datetime.datetime.now()
        timeout = timeout + datetime.timedelta(minutes=-10)
        terminals = Terminal.objects.filter(is_active=True).filter(last_connect__gte=timeout).order_by('metric').all()
        return terminals.first()
