from django.shortcuts import get_object_or_404, render
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from django.db.models import Max

from .models import Instructor

def index(request):
	query = request.GET.get('semester')
	template = "F3/index.html"
	context = {}
	context['data'] = Instructor.objects.raw('SELECT instructor.id, name, dept, COUNT(*) AS count FROM Takes INNER JOIN Teaches ON (Takes.course_ID, Takes.sec_id, Takes.year) = (Teaches.course_id, Teaches.sec_id, Teaches.year) INNER JOIN instructor ON Teaches.instr_id = instructor.ID and Teaches.semester = %s and Takes.semester = %s GROUP BY name;', [query, query])
	return render(request, template, context)
