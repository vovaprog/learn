#include <bits/stdc++.h>

#include <unistd.h>
#include <sys/time.h>

#include "../tools/Spinlock.h"

using namespace std;

int result = 0;

int tLocal(int x)
{
    thread_local int accum = 0;
    
    if(x < 50)
    {
        accum += x;
    }
    
    return accum;
}

void threadEntry()
{
    for(int i=0;i<100;++i)
    {
        result += tLocal(i);
    }
    
    cout <<result<<endl;
}


long long int getMilliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long long int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));		
}


int main()
{
    for(int i=0; i<4 ;++i)
    {
        new thread(threadEntry);
    }    
            
    return 0;    
}
