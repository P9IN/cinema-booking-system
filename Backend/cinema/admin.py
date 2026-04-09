from django.contrib import admin
from .models import Session, Movie, CinemaUser, Ticket
# Register your models here.


@admin.register(Session)
class SessionAdmin(admin.ModelAdmin):
    pass


@admin.register(Movie)
class MovieAdmin(admin.ModelAdmin):
    pass


@admin.register(Ticket)
class TicketAdmin(admin.ModelAdmin):
    pass
