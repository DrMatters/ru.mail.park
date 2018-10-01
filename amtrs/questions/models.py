# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db.models.signals import post_save
from django.dispatch import receiver
from django.db import models
from django.contrib.auth.models import User


class QuestionsManager(models.Manager):
    def list_new(self):
        return self.order_by('-id')

    def list_hot(self):
        return self.order_by('-rating')

    def list_by_tag(self, tag_name):
        return self.filter(tags__title=tag_name)


class Question(models.Model):
    title = models.CharField(verbose_name=u'question title',
                             max_length=100)
    text = models.TextField(verbose_name=u'question text',
                            max_length=420)
    author = models.ForeignKey('Profile', verbose_name=u'author')
    creation_date = models.DateTimeField(verbose_name=u'creation_date',
                                         auto_now_add=True)
    rating = models.IntegerField(default=0, verbose_name=u'question rating')

    tags = models.ManyToManyField('Tag')
    objects = QuestionsManager()

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'Question'
        verbose_name_plural = u'Questions'


class Tag(models.Model):
    title = models.CharField(verbose_name=u'tag title',
                             max_length=25, primary_key=True)

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'Tag'
        verbose_name_plural = u'Tags'


class ProfileManager(models.Manager):
    def for_user(self, user):
        return self.filter(user=user).first()

class Profile(models.Model):
    user = models.OneToOneField(User)
    registration_date = models.DateTimeField(verbose_name=u'Registration date',
                                             auto_now_add=True)
    avatar_link = models.CharField(verbose_name='Avatar path',
                                   max_length=55, default='no_avatar.jpg')

    objects = ProfileManager()

    def __unicode__(self):
        return self.user.username

    class Meta:
        verbose_name = u'Profile'
        verbose_name_plural = u'Profile'


class AnswersManager(models.Manager):
    def all_answers(self, parent):
        return self.filter(question=parent)


class Answer(models.Model):
    question = models.ForeignKey('Question',
                                 verbose_name=u'parent question')
    text = models.TextField(verbose_name=u'text',
                            max_length=410)
    user = models.ForeignKey('Profile',
                             verbose_name=u'user')
    rating = models.IntegerField(verbose_name=u'rating',
                                 default=0)
    creation_date = models.DateTimeField(verbose_name=u'creation date',
                                         auto_now_add=True)

    objects = AnswersManager()

    def __unicode__(self):
        return self.question.title

    class Meta:
        verbose_name = u'Answer'
        verbose_name_plural = u'Answers'


RATE = (
    (0, "+"),
    (1, "-")
)


class QuestionRating(models.Model):
    question = models.ForeignKey('Question', verbose_name=u"Rated element (question>")

    user = models.ForeignKey('Profile')
    delta = models.BooleanField(choices=RATE, verbose_name=u"Delta rate")

    def __unicode__(self):
        return self.question.title + str(self.RATE[self.delta][1])

    class Meta:
        verbose_name = u'Element rate (question)'
        verbose_name_plural = u'Elements ratings (question)'


class AnswerRating(models.Model):
    answer = models.ForeignKey('Answer', verbose_name=u"Rated element(answer")

    user = models.ForeignKey('Profile')
    delta = models.BooleanField(choices=RATE, verbose_name=u"Delta")

    def __unicode__(self):
        return self.answer.question.title

    class Meta:
        verbose_name = u'Element rate(answer)'
        verbose_name_plural = u'Element rate(answer)'
