from datetime import datetime, timedelta

start_date_string = '20161103'
number_of_days = 45
add = False



start_date = datetime.strptime(start_date_string, "%Y%m%d").date()

if add:
    result = start_date + timedelta(days=number_of_days)
else:
    result = start_date - timedelta(days=number_of_days)

print result

