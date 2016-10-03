#include <bits/stdc++.h>

#include "../SimpleProfiler.h"

using namespace std;

const int ITERS = 1000000;

long long int getMillisecondsClock()
{
    return clock() * 1000 / CLOCKS_PER_SEC;
}

long long int getMillisecondsTimeOfDay()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long long int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long int getMillisecondsChrono()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}


int main()
{
    long long int accum = 0;
    

    {
        SimpleProfiler prof("gettimeofday");
        
        for(int i=0;i<ITERS;++i)
        {            
            accum += getMillisecondsTimeOfDay();
        }
    }

    {
        SimpleProfiler prof("clock");
        
        for(int i=0;i<ITERS;++i)
        {
            accum += getMillisecondsClock();
        }
    }

    {
        SimpleProfiler prof("chrono");
        
        for(int i=0;i<ITERS;++i)
        {
            accum += getMillisecondsChrono();
        }
    }
    
    {
        SimpleProfiler prof("time + localtime");
        
        for(int i=0;i<ITERS;++i)
        {
            time_t rawtime;
            struct tm * timeinfo;

            time ( &rawtime );
            timeinfo = localtime ( &rawtime );            
            
            accum += timeinfo->tm_sec;
        }
    }
    
    {
        SimpleProfiler prof("time + ctime");
        
        for(int i=0;i<ITERS;++i)
        {
            time_t mytime;
            mytime = time(NULL);
            ctime(&mytime);
            //printf(ctime(&mytime));
        }
    }    

    {
        SimpleProfiler prof("chrono + ctime");
        
        for(int i=0;i<ITERS;++i)
        {
            std::time_t t = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            std::ctime(&t);
            //printf(ctime(&t));
        }
    }    
    
    

    
    cout <<accum<<endl;
    
    return 0;
}


