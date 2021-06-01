from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.db.models import Max

from .models import Instructor

def index(request):
    return render(request, 'F2/index.html', context)
		
class IndexView(generic.ListView):
	def get_queryset(self):
		return Instructor.objects.raw('select id, name, dept, avg(salary) as avg_salary, min(salary) as min_salary, max(salary) as max_salary from instructor group by dept')
	
	template_name = 'F2/index.html'
	context_object_name = 'data'