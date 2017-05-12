#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <IncPerSecond.h>

struct StringData {
	char str[11];
};

bool cdInit(unsigned int dataCountArg);
bool cdItoa(unsigned int *dataInput, StringData *stringDataOutput);

void uintToString(unsigned int x, char *output)
{
	const int bufSize = 11;
	char buf[bufSize];
	buf[bufSize - 1] = 0;
	int ind = bufSize - 2;
	
	do {
		buf[ind] = '0' + x % 10;
		x /= 10;
		--ind;
	} while (x != 0);

	++ind;

	int i;
	for(i = 0; buf[ind] != 0; ++i, ++ind)
	{
		output[i] = buf[ind];
	}
	output[i] = 0;
}


const int dataCount = 1024 * 1024;
unsigned int *dataInput = new unsigned int[dataCount];
StringData *stringsOutput = new StringData[dataCount];
IncPerSecond incPerSecond(1000000);

void cpuRun()
{
	while(true)
	{		
		for (int i=0;i<dataCount;++i)
		{
			sprintf(stringsOutput[i].str, "%u", dataInput[i]);
			//itoa(dataInput[i], stringsOutput[i].str, 10);
			//uintToString(dataInput[i], stringsOutput[i].str);
		}
		incPerSecond.addAndPrint(dataCount);
	}
}

void cdRun()
{
	while(true)
	{		
		cdItoa(dataInput, stringsOutput);
		incPerSecond.addAndPrint(dataCount);
	}
}

void check()
{
	for (int i=0;i<dataCount;++i)
	{
		uintToString(dataInput[i], stringsOutput[i].str);
	}

	StringData *stringsOutput2 = new StringData[dataCount];
	
	cdItoa(dataInput, stringsOutput2);
	
	for (int i=0;i<dataCount;++i)
	{
		if(strcmp(stringsOutput[i].str, stringsOutput2[i].str) != 0)
		{
			printf("error!\n");
			exit(-1);
		}
	}
	printf("ok\n");
}

int main()
{	
	srand(time(NULL));
	
	for (int i=0;i<dataCount;++i)
	{
		dataInput[i] = rand();	
	}
	
	cdInit(dataCount);
	
	//cpuRun();
	cdRun();	
	//check();
}

