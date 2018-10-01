# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin

from questions.models import Question, Tag, Profile, Answer, AnswerRating, QuestionRating



admin.site.register(Question)
admin.site.register(Tag)
admin.site.register(Profile)
admin.site.register(Answer)
admin.site.register(AnswerRating)
admin.site.register(QuestionRating)


