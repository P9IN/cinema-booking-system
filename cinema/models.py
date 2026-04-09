from django.db import models

# Create your models here.
from django.contrib.auth.models import AbstractUser


class CinemaUser(AbstractUser):
    phone = models.TextField(null=True,blank=True)
    age = models.IntegerField(default=18)

    def __str__(self):
        return self.username


class Movie(models.Model):
    name = models.TextField()
    rating = models.FloatField()
    genre = models.TextField()
    age = models.IntegerField()

    def __str__(self):
        return self.name


class Session(models.Model):
    date = models.DateTimeField()
    price = models.IntegerField()
    movie = models.ForeignKey(Movie, on_delete=models.CASCADE)


class Ticket(models.Model):
    user = models.ForeignKey(CinemaUser, on_delete=models.CASCADE)
    session = models.ForeignKey(Session, on_delete=models.CASCADE)
    seat = models.IntegerField()
