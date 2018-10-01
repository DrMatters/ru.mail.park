from django.conf.urls import url

from views import new_questions_list, question_details, questions_by_tag_list, login_view, register, ask, settings, hot_questions_list


urlpatterns = [
    url(r'^hot/', hot_questions_list.as_view(), name='hot_list'),
    url(r'^$', new_questions_list.as_view(), name='new_list'),
    url(r'^tag/(?P<tag>[\w-]+)/$', questions_by_tag_list.as_view(), name='tag_list'),
    url(r'^question/(?P<question_id>[0-9]+)/$', question_details.as_view(), name='question_details'),
    url(r'^login/', login_view.as_view(), name='login'),
    url(r'^signup/', register.as_view(), name='register'),
    url(r'^ask/', ask.as_view(), name='ask'),
    url(r'^settings/', settings.as_view(), name='settings')
]
