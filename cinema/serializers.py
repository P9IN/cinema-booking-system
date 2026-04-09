from rest_framework import serializers
from .models import Session, Movie, Ticket


class MovieSerializer(serializers.ModelSerializer):
    class Meta:
        model = Movie
        fields = ['name', 'rating', 'genre', 'age']


class SessionSerializer(serializers.ModelSerializer):
    movie = MovieSerializer()  # Добавляем сериализацию Movie

    class Meta:
        model = Session
        fields = '__all__'

class TicketSerializer(serializers.ModelSerializer):
    class Meta:
        model = Ticket
        fields = '__all__'
