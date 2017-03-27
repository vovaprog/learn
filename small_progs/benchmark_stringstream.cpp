#include <bits/stdc++.h>

#include "../SimpleProfiler.h"

using namespace std;

string runStringAppend(int appendCount)
{
	string s;

	for(int i=0;i<appendCount;++i)
	{
		s.append("12345");
	}
	return s;
}

string runStringAppendCount(int appendCount)
{
	string s;

	for(int i=0;i<appendCount;++i)
	{
		s.append("12345", 5);
	}
	return s;
}

string runStringPlus(int appendCount)
{
	string s;

	for(int i=0;i<appendCount;++i)
	{
		s += "12345";
	}
	return s;
}

string runStringStream(int appendCount)
{
	ostringstream ss;
	for(int i=0;i<appendCount;++i)
	{
		ss << "12345";
	}
	return ss.str();
}


int main()
{
	const int iterCount = 10000;
	const int appendCount = 10000;

	long long int sum = 0;
	
    {
        SimpleProfiler prof("string.append");

        for(int i=0;i<iterCount;++i)
        {
        	sum += runStringAppend(appendCount).size();	
        }        
    }

    {
        SimpleProfiler prof("string.append count");

        for(int i=0;i<iterCount;++i)
        {
        	sum += runStringAppendCount(appendCount).size();	
        }        
    }
    
	{
        SimpleProfiler prof("stringstream");

        for(int i=0;i<iterCount;++i)
        {
        	sum += runStringStream(appendCount).size();	
        }        
    }

    {
        SimpleProfiler prof("string +=");

        for(int i=0;i<iterCount;++i)
        {
        	sum += runStringPlus(appendCount).size();	
        }        
    }
    
    cout <<sum<<endl;
	
    return 0;
}
