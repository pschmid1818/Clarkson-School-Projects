#SELECT title, course_id, sec_id, semester, year, dept FROM Teaches NATURAL JOIN course WHERE semester = 1 and year = 2020 ORDER BY dept, year, semester

from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.db import connection

from .models import Teaches
from .models import Course

def index(request):
	query1 = request.GET.get('semester')
	query2 = request.GET.get('year')
	template = "F6/index.html"
	context = {}
	context['data'] = Teaches.objects.raw('SELECT instr_id, title, course_id, sec_id, semester, year, dept FROM Teaches NATURAL JOIN course WHERE semester = %s and year = %s ORDER BY dept, title;', [query1, query2])
	return render(request, template, context)