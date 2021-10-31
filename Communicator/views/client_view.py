from django.shortcuts import render

# Create your views here.
from rest_framework.authentication import TokenAuthentication, SessionAuthentication
from rest_framework.decorators import permission_classes
from rest_framework.generics import GenericAPIView
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework_swagger import renderers

from Communicator.api.serializers import PingSerializer


class PingView(APIView):

    authentication_classes = [TokenAuthentication, SessionAuthentication]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        return Response({"Ok"})

    def post(self, request):
        serializer = PingSerializer(data=request.data)
        if serializer.is_valid(raise_exception=True):
            article_saved = serializer.save()
        return Response({"success": "Article '{}' created successfully"})