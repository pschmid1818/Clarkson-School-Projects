from django.urls import path

from . import views
from .views import index

app_name = 'F1'
urlpatterns = [
    path('', index, name='index'),
]