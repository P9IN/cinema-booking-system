from django.shortcuts import render
from rest_framework import status
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import AllowAny, IsAuthenticated
from rest_framework.response import Response
from rest_framework.request import Request
from .models import Session
from datetime import datetime
from .serializers import SessionSerializer, TicketSerializer
# Create your views here.


@api_view(['GET'])
def get_sessions(request: Request) -> Response:
    now = datetime.now()
    sessions = Session.objects.filter(date__gt=now)
    session = sessions.first()
    serializer = SessionSerializer(session)
    return Response(serializer.data, status.HTTP_200_OK)


@api_view(['POST'])
@permission_classes([IsAuthenticated])
def buy_ticket(request: Request) -> Response:
    ticketJson = {
        "user": request.user.id,
        "session": request.data.get('session'),
        "seat": request.data.get('seat')
    }
    serializer = TicketSerializer(data=ticketJson)
    if serializer.is_valid(raise_exception=True):
        serializer.save()
    return Response()
