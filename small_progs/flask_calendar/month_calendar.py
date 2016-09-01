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

@app.route('/')
@requires_auth
def page():
    cal = Calendar(0)
    
    month = cal.monthdatescalendar(2016, 9)
    
    for week in month:
        print week
    
    return render_template('page.html', data={'month':month})


if __name__ == "__main__":
    app.debug = True
    app.run(host='0.0.0.0')    




 