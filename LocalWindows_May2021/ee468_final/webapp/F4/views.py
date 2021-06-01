#SELECT course_id, sec_id, COUNT(*) FROM Teaches NATURAL JOIN Takes GROUP BY course_id, sec_id;

from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.db import connection

from .models import Teaches
from .models import Takes
from .models import Instructor

def index(request):
	query1 = request.GET.get('name')
	query2 = request.GET.get('semester')
	template = "F4/index.html"
	context = {}
	context['data'] = Teaches.objects.raw('SELECT instr_id, Teaches.year, course_id, sec_id, COUNT(*) as co FROM Teaches NATURAL JOIN Takes join Instructor WHERE Teaches.instr_id = Instructor.id and Instructor.name = %s and semester = %s GROUP BY course_id, sec_id;', [query1, query2])
	return render(request, template, context)
