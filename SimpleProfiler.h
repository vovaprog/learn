#pragma once

#include <string>

#ifdef __linux__
#   include <unistd.h>
#   include <sys/time.h>
#else
#   include <windows.h>
#endif

class SimpleProfiler{
public:
    SimpleProfiler(const std::string &name):name(name)
    {
        startMillis=getMilliseconds();
    }
    
    ~SimpleProfiler()
    {
        unsigned int millisPassed = getMilliseconds() - startMillis;
        
        std::cout << name <<": "<<millisPassed<<std::endl;
    }
    
    unsigned int getMilliseconds()
    {
    #ifdef __linux__
        struct timeval tv;
        gettimeofday(&tv, 0);
        return (unsigned int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));		
    #else
        return GetTickCount();
    #endif
    }

private:
    unsigned int startMillis;
    std::string name;
};


