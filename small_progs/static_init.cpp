#include <bits/stdc++.h>

using namespace std;

int init(int x)
{
	printf("init function: %d\n", x);
	return x * x;
}


void testStaticInit(int x)
{
	static int myResult = init(x);
	
	if (myResult == 0)
	{
		return;	
	}
	
	printf("%d ", x);
}


int main()
{
	for(int i=1;i<=10;++i)
	{
		testStaticInit(i);	
	}		
	
    return 0;
}
