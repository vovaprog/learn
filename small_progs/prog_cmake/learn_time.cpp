#include <time.h>
#include <iostream>

using namespace std;

#define RFC1123FMT "%a, %d %b %Y %H:%M:%S GMT"

void learn_time1()
{
	const char *buf = "Tue, 01 Nov 2016 14:44:00 GMT";

	struct tm time_data;
	if(strptime(buf, RFC1123FMT, &time_data) == NULL)
	{
		return;
	}
	time_t resultGm = timegm(&time_data);
	time_t resultLocal = timelocal(&time_data);
	time_t now = time(NULL);

	cout << "local: " << resultLocal << endl;
	cout << "gm   : "<< resultGm << endl;
	cout << "now  : " << now << endl;
}

