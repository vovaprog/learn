
from calendar import Calendar
from datetime import date

cal = Calendar(0)

month = cal.monthdatescalendar(2016, 6)

for week in month:
    print week

 