#include <bits/stdc++.h>

#include <unistd.h>
#include <sys/time.h>

#include "../tools/Spinlock.h"

using namespace std;

/*
4 threads core i7:

spinlock:
t: 21477497
t: 24651517
t: 24563029
t: 22150398

mutex:
t: 3860123
t: 3763813
t: 3848070
t: 3780573
*/


long long int prevX = 0;
long long int x = 0;
atomic_int runFlag;
mutex mtx;

long long int prevMillis = 0;

Spinlock spinlock; 

void threadEntry()
{
    while(true)
    {
       {
           //std::unique_lock<std::mutex> lock(mtx);
           std::lock_guard<std::mutex> lock(mtx);
           ++x;           
       }       
       std::this_thread::yield();
    }
}

void threadEntry2()
{
    while(true)
    {
       {
           std::lock_guard<Spinlock> lock(spinlock);           
           ++x;           
       }       
       //std::this_thread::yield();
    }
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
        new thread(threadEntry2);
    }    
    
    for(long long int i=0;;++i)
    {
        if(i % 100000==0)
        {
            long long int millis = getMilliseconds();
            
            if(getMilliseconds() - prevMillis > 1000)
            {
                long long int xCopy;
                
                {
                   //std::lock_guard<std::mutex> lock(mtx);
                   std::lock_guard<Spinlock> lock(spinlock);
                   xCopy = x;
                }       
                                
                if(prevX > 0)
                {
                    cout << "t: " << (xCopy - prevX) << endl;
                }
                prevX = xCopy;
                
                prevMillis = getMilliseconds();
            }
        }            
    }        
        
    return 0;    
}
