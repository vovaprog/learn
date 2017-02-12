#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int getExecutableName(char *buf, size_t bufSize)
{
	const size_t procExeNameSize = 50;
	char procExeName[procExeNameSize];
	if(snprintf(procExeName, procExeNameSize, "/proc/%lld/exe", (long long int)getpid()) >= procExeNameSize)
	{
		return ENOMEM;
	}
	
	int bytes = readlink(procExeName, buf, bufSize - 1);
	
	if(bytes < 0)
	{
		return errno;	
	}
	
	buf[bytes] = 0;
	
	return 0;
}

int main()
{
	char buf[500];
	
	if(getExecutableName(buf, sizeof(buf)) == 0)
	{
		printf("executable name: [%s]\n", buf);	
	}
	
	return 0;
}


