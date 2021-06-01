from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic

from .models import Instructor

def index(request):
	template = "functions/index.html"
	context = {}
	context['data'] = Instructor.objects.order_by('name')
	return render(request, template, context)