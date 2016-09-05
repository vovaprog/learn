#ifndef INC_PER_SECOND_H
#define INC_PER_SECOND_H

#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <atomic>
#include <chrono>


class IncPerSecond
{
public:
    IncPerSecond() = default;

    IncPerSecond(unsigned int checkInterval): checkInterval(checkInterval) { }


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
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch()
               ).count();
    }


    long long int prevMillis = 0;
    long long int counter = 0;
    long long int prevCounter = 0;
    unsigned int checkInterval = 1000;
};

#endif // INC_PER_SECOND_H

