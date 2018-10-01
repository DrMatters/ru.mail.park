from django.contrib.auth.models import User
from django import forms
from questions.models import Question, Tag, Profile, Answer


class LoginForm(forms.Form):
    login = forms.CharField(label='login', max_length=127)
    password = forms.CharField(label='password', widget=forms.PasswordInput)


class QuestionForm(forms.Form):
    title = forms.CharField(label="Title", max_length=127)
    tags = forms.CharField(label="Tags", max_length=420)
    text = forms.CharField(label="Text",
                           widget=forms.Textarea, max_length=420)

    def save(self, user):

        question = Question(
            title=self.cleaned_data['title'],
            text=self.cleaned_data['text'],
            author=Profile.objects.filter(user=user).first(),
        )
        question.save()
        return question._get_pk_val()

