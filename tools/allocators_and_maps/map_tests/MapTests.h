#ifndef MAP_TESTS_INCLUDED
#define MAP_TESTS_INCLUDED

#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

inline long long int getMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}


#define MY_ASSERT(condition) \
if(!(condition)) \
{ \
    printf("assertion failed: %s\n", #condition); \
    exit(-1); \
}



template<typename MapType, int itemCount, int iterationCount, int step = 10>
void mapInsertEraseTest()
{
    MapType m;

    for(int q = 0; q < iterationCount; ++q)
    {
        for(int i = 0; i < itemCount; ++i)
        {
            m[i] = i;
        }

        for(int start = 0; start < step; ++start)
        {
            for(int i = start; i < itemCount; i += step)
            {
                m.erase(i);
            }
        }

        MY_ASSERT(m.size() == 0);

        for(int start = 0; start < step; ++start)
        {
            for(int i = start; i < itemCount; i += step)
            {
                m[i] = i;
            }
        }

        for(int i = 0; i < itemCount; ++i)
        {
            m.erase(i);
        }

        MY_ASSERT(m.size() == 0);
    }
}


template<int stringLength>
std::string generateRandomString()
{
    char buf[stringLength + 1];

    for(int i = 0; i < stringLength; ++i)
    {
        buf[i] = (char)((rand() % 26) + 'a');
    }

    buf[stringLength] = 0;

    return std::string(buf);
}


template<typename MapType, int iterCount>
void searchTest(const char *title, const vector<string> & items)
{
    MapType m;

    for(const string & s : items)
    {
        m[s] = s;
    }

    {
        long long int millis = getMilliseconds();

        for(int q = 0; q < iterCount; ++q)
        {
            for(const string & key : items)
            {
                if(m.find(key) == m.end())
                {
                    printf("key not found!\n");
                    exit(-1);
                }
            }
        }

        cout << title << ": " << getMilliseconds() - millis << endl;
    }
}

#endif
