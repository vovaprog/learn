//===========================================================================================
//===========================================================================================
//===========================================================================================

#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <atomic>

std::atomic_llong tCounter;
//long long int tCounter;
long long int prevMillis = 0;
long long int prevCounter = 0;

inline long long int getMilliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long long int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

inline void execsPerSec()
{
	long long int counter = ++tCounter;

	if((counter & 0xffff) == 0)
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

//===========================================================================================
//===========================================================================================
//===========================================================================================


int main()
{
    for(long long int i=0;;++i)
    {
        execsPerSec();
    }

    return 0;    
}
