#SELECT name, course_id, sec_id, year FROM Takes NATURAL JOIN students ORDER BY year, sec_id, course_id

from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.db import connection

from .models import Students
from .models import Takes
from .models import Teaches
from .models import Instructor

def index(request):
	query1 = request.GET.get('name')
	query2 = request.GET.get('semester')
	template = "F5/index.html"
	context = {}
	context['data'] = Students.objects.raw('SELECT Student.id, Student.name, course_id, sec_id, year FROM Takes NATURAL JOIN Teaches NATURAL JOIN student join Instructor WHERE Instructor.id = Teaches.instr_id and Instructor.name = %s and semester = %s ORDER BY year, sec_id, course_id', [query1, query2])
	return render(request, template, context)
