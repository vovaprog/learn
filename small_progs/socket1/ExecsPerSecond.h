#ifndef EXECS_PER_SECOND_H
#define EXECS_PER_SECOND_H

#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <atomic>


class ExecsPerSecond {
public:
    ExecsPerSecond() = default;
    
    ExecsPerSecond(unsigned int checkInterval): checkInterval(checkInterval)
    {
    }
    
    inline void inc()
    {
        ++counter;
    }
    inline void print()
    {
        if(counter - prevCounter >= checkInterval)
        {
            long long int millis = getMilliseconds();
    
            if(millis - prevMillis > 1000)
            {
                if(prevMillis > 0)
                {
                    std::cout << "t: " << (counter - prevCounter) << std::endl;
                }
    
                prevCounter = counter;
                prevMillis = millis;
            }
        }
    }
    inline void incAndPrint()
    {
        inc();
        print();
    }
    
    inline void addAndPrint(long long int add)
    {
        counter += add;
        print();
    }
    
private:
    inline long long int getMilliseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return (((long long int)tv.tv_sec * 1000) + ((long long int)tv.tv_usec / 1000));
    }    
    
    long long int prevMillis = 0;
    long long int counter = 0;
    long long int prevCounter = 0;
    unsigned int checkInterval = 1000;
};

#endif

