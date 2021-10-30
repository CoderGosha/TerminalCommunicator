from django.shortcuts import render

# Create your views here.
from rest_framework.response import Response
from rest_framework.views import APIView

from Communicator.api.serializers import PingSerializer


class PingView(APIView):
    def post(self, request):
        ping = request.data.get('ping')
        serializer = PingSerializer(data=ping)
        if serializer.is_valid(raise_exception=True):
            article_saved = serializer.save()
        return Response({"success": "Article '{}' created successfully"})