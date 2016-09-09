from flask import Flask
from functools import wraps
from flask import request, Response, redirect
from flask import render_template
from calendar import Calendar
from datetime import date
import calendar
from flask.ext.wtf import Form
from wtforms import BooleanField, StringField, PasswordField, validators, HiddenField, SubmitField
import sqlite3
from flask import g
import os
import storage
import re


if __name__ == "__main__":
    app = Flask(__name__)
    app.config.from_object('config')


@app.teardown_appcontext
def close_connection(exception):
    storage.close()

   


def check_auth(username, password):
    """This function is called to check if a username /
    password combination is valid.
    """
    return username == 'admin' and password == '123'

def authenticate():
    """Sends a 401 response that enables basic auth"""
    return Response(
    'Could not verify your access level for that URL.\n'
    'You have to login with proper credentials', 401,
    {'WWW-Authenticate': 'Basic realm="Login Required"'})

def requires_auth(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        auth = request.authorization
        if not auth or not check_auth(auth.username, auth.password):
            return authenticate()
        return f(*args, **kwargs)
    return decorated

def get_prev_month(year, month):
    if month == 1:
        return year-1, 12
    else:
        return year, month - 1

def get_next_month(year, month):
    if month == 12:
        return year+1, 1
    else:
        return year, month + 1

class TaskEditForm(Form):
    date = HiddenField('date')
    id = HiddenField('id')
    task_text = StringField('text', [validators.Length(min=0, max=1000)])
    submit_edit = SubmitField(label='ok')
    submit_done = SubmitField(label='done')
    submit_delete = SubmitField(label='delete')
    



@app.route('/save-task', methods = ['GET', 'POST'])
@requires_auth
def save_task_page():
    form = TaskEditForm()
    if form.validate_on_submit():
        id = int(form.id.data)

        if form.submit_delete.data == True:
            storage.delete_task(id)
        elif form.submit_done.data == True:
            storage.edit_task(id, form.date.data, form.task_text.data, 'done')
        else:
            if id < 0:
                storage.create_task(form.date.data, form.task_text.data)
            else:
                storage.edit_task(id, form.date.data, form.task_text.data)

        return redirect("/{0}".format(form.date.data))
    else:
        return render_template('edit-task.html', form=form)

@app.route('/create-task/<date>')
@requires_auth
def create_task_page(date):
    form = TaskEditForm()
    form.date.data = date
    form.id.data = -1
    return render_template('edit-task.html', form=form)

@app.route('/edit-task/<id>')
@requires_auth
def edit_task_page(id):
    r = storage.get_task(id)
    
    form = TaskEditForm()
    form.id.data = id
    form.date.data = r['date']
    form.task_text.data = r['task']

    return render_template('edit-task.html', form=form)


def parse_date(date):
    m = re.match("^([0-9]{4})-([0-9]{1,2})(-([0-9]{1,2}))?$", date)
    if m:
        year = m.group(1)
        month = m.group(2)
        if len(m.groups())>4:
            day = m.group(4)
        else:
            day = 0
        return int(year), int(month), int(day)
    return 0, 0, 0

def date_to_string(year, month, day=0):
    if day != 0:
        return "{0}-{1:0>2}-{2:0>2}".format(year, month, day)
    else:
        return "{0}-{1:0>2}".format(year, month)

@app.route('/',defaults={'page_date':''})
@app.route('/<page_date>')
@requires_auth
def calendar_page(page_date):    
    year, month, day = parse_date(page_date)

    if year==0 or month==0:
        now = date.today()
        year = now.year
        month = now.month

    cal = Calendar(0)    
    month_cal = cal.monthdatescalendar(year, month)

    date_start = month_cal[0][0]
    date_end = month_cal[len(month_cal)-1][len(month_cal[len(month_cal)-1])-1]
    
    tasks = storage.get_tasks(date_start, date_end)

    month_data = []

    for week in month_cal:
        week_data = []
        for day in week:
            print day
            day_data = {}
            day_data['day'] = day.day
            day_data['create_task_link'] = '/create-task/{0}-{1:0>2}-{2:0>2}'.format(day.year, day.month, day.day)
            day_data['tasks'] = []
            for task in tasks:
                if str(day) == task['date']:
                    task_data = {}
                    task_data['id'] = task['id']
                    task_data['date'] = task['date']
                    task_data['task'] = task['task']
                    task_data['edit_link'] = '/edit-task/{0}'.format(task['id']) 
                    day_data['tasks'].append(task_data)
            
            week_data.append(day_data)
        month_data.append(week_data)        

    data={'month':month_data}
    
    prev_year, prev_month = get_prev_month(year, month)
    next_year, next_month = get_next_month(year, month)

    data['prev_month_link'] = str.format('/{0}', date_to_string(prev_year, prev_month))
    data['next_month_link'] = str.format('/{0}', date_to_string(next_year, next_month))    

    data["title"] = "{0} {1}".format(year, calendar.month_name[month])

    return render_template('page.html', data = data)



if __name__ == "__main__":
    app.debug = True
    app.run(host='0.0.0.0')    




 