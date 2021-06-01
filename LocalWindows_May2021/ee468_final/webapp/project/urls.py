"""demo_django URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path
from django.views.generic.base import TemplateView

urlpatterns = [
	path('functions/', include('functions.urls')),
	path('F6/', include('F6.urls')),
	path('F5/', include('F5.urls')),
	path('F4/', include('F4.urls')),
	path('F3/', include('F3.urls')),
	path('F2/', include('F2.urls')),
	path('F1/', include('F1.urls')),
	path('polls/', include('polls.urls')),
	path('user/', include('django.contrib.auth.urls')),
	path('', TemplateView.as_view(template_name='home.html'), name='home'),
    path('admin/', admin.site.urls),
]
