from flask import Flask
from functools import wraps
from flask import request, Response
from flask import render_template
from calendar import Calendar
from datetime import date
import calendar
from wtforms import Form, BooleanField, StringField, PasswordField, validators


if __name__ == "__main__":
    app = Flask(__name__)


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
    text = StringField('text', [validators.Length(min=0, max=1000)])
    

@app.route('/create-task/<year>/<month>/<day>')
@requires_auth
def create_task_page(year, month, day):
    form = TaskEditForm()
    return render_template('edit-task.html', form=form)


@app.route('/calendar',defaults={'year':0, 'month':0})
@app.route('/calendar/<year>/<month>')
@requires_auth
def calendar_page(year, month):
    year = int(year)
    month = int(month)
    if year==0 or month==0:
        now = date.today()
        year = now.year
        month = now.month

    cal = Calendar(0)    
    month_cal = cal.monthdatescalendar(year, month)

    month_data = []

    for week in month_cal:
        week_data = []
        for day in week:
            day_data = {}
            day_data['day'] = day.day
            day_data['create_task_link'] = '/create-task/{0}/{1}/{2}'.format(day.year, day.month, day.day)
            week_data.append(day_data)
        month_data.append(week_data)        

    data={'month':month_data}
    
    prev_year, prev_month = get_prev_month(year, month)
    next_year, next_month = get_next_month(year, month)

    data['prev_month_link'] = str.format('/{0}/{1}', prev_year, prev_month)
    data['next_month_link'] = str.format('/{0}/{1}', next_year, next_month)    

    data["title"] = "{0} {1}".format(year, calendar.month_name[month])

    return render_template('page.html', data = data)



if __name__ == "__main__":
    app.debug = True
    app.run(host='0.0.0.0')    




 