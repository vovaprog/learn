#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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

int getStartupPath(char *buf, size_t bufSize)
{
	int ret = getExecutableName(buf, bufSize);
	
	if(ret != 0)
	{
		return ret;
	}
	
	int length = strlen(buf);
	
	int i;
	for(i = length - 1; i > 0; --i)
	{
		if(buf[i] == '/')
		{
			break;
		}
	}
	
	for(; i - 1 >= 0; --i)
	{
		if(buf[i - 1] != '/')
		{
			break;
		}
	}

	if(buf[i - 1] == '/')
	{
		return EINVAL;
	}
	
	buf[i] = 0;
	
	return 0;
}

int main()
{
	char buf[500];
	
	if(getExecutableName(buf, sizeof(buf)) == 0)
	{
		printf("executable name: [%s]\n", buf);	
	}

	if(getStartupPath(buf, sizeof(buf)) == 0)
	{
		printf("startup path: [%s]\n", buf);	
	}
	
	return 0;
}


