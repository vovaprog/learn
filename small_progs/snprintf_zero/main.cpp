#include <iostream>
#include <thread>

using namespace std;

// check that snprintf appends null terminator to buf
// if output size is bigger than buf size;
int main()
{
	char buf[10] = {};
	
	int printMaxCount = 5;
	
	snprintf(buf, printMaxCount, "12345678901234567890");

	if(buf[printMaxCount - 1] != 0)
	{
		printf("null terminator was not added!\n");
		return -1;
	}

	for (int i=0;i<10;++i)
	{
		cout << i << ": " << (int) buf[i] << endl;		
	}

    return 0;
}


