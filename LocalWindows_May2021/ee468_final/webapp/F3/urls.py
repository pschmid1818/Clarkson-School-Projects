from django.urls import path

from . import views
from .views import index

app_name = 'F3'
urlpatterns = [
    path('', index, name='index'),
]