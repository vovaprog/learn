from flask import Flask
from functools import wraps
from flask import request, Response
from flask import render_template
from calendar import Calendar
from datetime import date

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


@app.route('/',defaults={'year':0, 'month':0})
@app.route('/<year>/<month>')
@requires_auth
def page(year, month):
    year = int(year)
    month = int(month)
    if year==0 or month==0:
        now = date.today()
        year = now.year
        month = now.month

    cal = Calendar(0)    
    month_cal = cal.monthdatescalendar(year, month)

    data={'month':month_cal}
    
    prev_year, prev_month = get_prev_month(year, month)
    next_year, next_month = get_next_month(year, month)

    data['prev_month_link'] = str.format('/{0}/{1}', prev_year, prev_month)
    data['next_month_link'] = str.format('/{0}/{1}', next_year, next_month)

    return render_template('page.html', data = data)


if __name__ == "__main__":
    app.debug = True
    app.run(host='0.0.0.0')    




 