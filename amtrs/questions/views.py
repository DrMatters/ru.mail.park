# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.views.generic import TemplateView
from django.shortcuts import get_object_or_404
from django.http import Http404, HttpResponseRedirect
from django.core.paginator import Paginator, EmptyPage
from django.contrib.auth import authenticate, login
from django.template.response import TemplateResponse

from questions.models import Question, Tag, Profile, Answer
from questions.forms import QuestionForm, LoginForm


def paginate(object_list, request, items_per_page):
    try:
        page_number = int(request.GET.get('page', 1))
    except ValueError:
        raise Http404
    paginator = Paginator(object_list, items_per_page)
    try:
        page = paginator.page(page_number)
    except EmptyPage:
        page = paginator.page(paginator.num_pages)
    return page


class new_questions_list(TemplateView):
    def get(self, request):
        response = TemplateResponse(request,
                                    'index.html',
                                    {
                                        'title': 'amtrs - new questions',
                                        'onpage_title': 'new questions',
                                        'questions': paginate(Question.objects.list_new(),
                                                              request, 20),
                                    })
        return response


class hot_questions_list(TemplateView):
    def get(self, request):
        response = TemplateResponse(request,
                                    'index.html',
                                    {
                                        'title': 'amtrs - hot questions',
                                        'onpage_title': 'hot questions',
                                        'questions': paginate(Question.objects.list_hot(),
                                                              request, 20),
                                    })
        return response


class questions_by_tag_list(TemplateView):
    def get(self, request, tag):
        tag_key = Tag.objects.filter(pk=tag)
        response = TemplateResponse(request, 'index.html',
                                    {
                                        'title': 'amtrs - by tag',
                                        'onpage_title': 'questions by tag: ' + tag,
                                        'questions': paginate(Question.objects.list_by_tag(tag_key),
                                                              request, 20)
                                    })
        return response


class question_details(TemplateView):
    def get(self, request, question_id):
        question = get_object_or_404(Question,
                                     pk=question_id)
        response = TemplateResponse(request, 'question.html',
                                    {
                                        'title': 'amtrs - give an answer',
                                        'onpage_title': question.title,
                                        'question': question,
                                        'answers': paginate(Answer.objects.all_answers(question), request, 3),
                                    })
        return response


class login_view(TemplateView):
    def get(self, request):
        form = LoginForm()

        response = TemplateResponse(request, 'login.html',
                                    {
                                        'title': 'amtrs - log in',
                                        'onpage_title': 'log in',
                                        'form': form,
                                    })
        return response

    def post(self, request):
        form = LoginForm(request.POST)

        if form.is_valid():
            cur_user = authenticate(username=form.cleaned_data['login'],
                                    password=form.cleaned_data['password'])

            if cur_user.is_active:

                login(request, cur_user)

                return HttpResponseRedirect('/')
            else:
                response = TemplateResponse(request, 'login.html',
                                            {
                                                'title': 'amtrs - log in',
                                                'onpage_title': 'log in',
                                                'form': form,
                                            })
                return response
        else:
            response = TemplateResponse(request, 'login.html',
                                        {
                                            'title': 'amtrs - log in',
                                            'onpage_title': 'log in',
                                            'form': form,
                                        })
            return response


class register(TemplateView):
    def get(self, request):
        response = TemplateResponse(request, 'register.html',
                                    {
                                        'title': 'amtrs - register',
                                        'onpage_title': 'register',
                                    })
        return response

    def post(self, request):
        form = RegisterForm(request.POST)

        if form.is_valid():
            return HttpResponseRedirect('/')
        else:
            return TemplateResponse(request, '')


'''
def signup(request):
    return render(request, 'register.html')
'''


class ask(TemplateView):
    def get(self, request):
        if request.user.is_authenticated():
            form = QuestionForm();
            response = TemplateResponse(request,
                                        'ask.html', {
                                            'title': 'amtrs - make a question',
                                            'onpage_title': 'ask',
                                            'form': form,
                                        })
            return response
        else:
            return HttpResponseRedirect('/login')

    def post(self, request):
        form = QuestionForm(request.POST)
        if form.is_valid():
            current_id = form.save(request.user)
            return HttpResponseRedirect('/question/' + str(current_id))
        else:
            response = TemplateResponse(request,
                                        'ask.html', {
                                            'title': 'amtrs - make a question',
                                            'onpage_title': 'ask',
                                            'form': form,
                                        })
            return response


class settings(TemplateView):
    def get(self, request):
        response = TemplateResponse(request, 'settings.html',
                                    {
                                        'title': 'amtrs - register',
                                        'onpage_title': 'register',
                                    })
        return response
