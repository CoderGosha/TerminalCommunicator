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
        if not request.user.has_perm('Communicator.add_event'):
            return Response({}, status=status.HTTP_403_FORBIDDEN)

        self.delete_old_task()
        serialazer = EventRequestSerializer(data=request.data)
        if serialazer.is_valid(raise_exception=True):
            terminal = self.get_terminal()
            if terminal is None:
                return Response({'status': 'terminal not found'}, status=status.HTTP_404_NOT_FOUND)
            data_create = datetime.datetime.now()
            data_expired = data_create + datetime.timedelta(hours=1)
            event = serialazer.save(owner=self.request.user, terminal=terminal, data_create=data_create,
                                    data_expired=data_expired)
            return Response({"success": "Ok", "id": event.id})

    '''
        Выберем все активные терминалы и отсортируем по метрике (добавить ротацию)
    '''

    def get_terminal(self) -> Terminal:
        timeout = datetime.datetime.now()
        timeout = timeout + datetime.timedelta(minutes=-10)
        terminals = Terminal.objects.filter(is_active=True).filter(last_connect__gte=timeout).order_by('metric').all()
        return terminals.first()

    '''
        Перенести метод в отдельный таск 
    '''

    def delete_old_task(self):
        timeout = datetime.datetime.now()
        events = Event.objects.filter(owner=self.request.user).filter(data_expired__lt=timeout).delete()



