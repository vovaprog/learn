#include <BlockAllocator.h>
#include <TrivialAllocator.h>

#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <chrono>

using namespace std;

void trivialAllocatorTest()
{
    {
        list<int, TrivialAllocator<int>> lst;

        for(int i = 1; i <= 10; ++i)
        {
            lst.push_back(i);
        }
    }

    printf("\n\n\n");

    {
        printf("sizeof(pair<const int, int>): %zu\n", sizeof(pair<const int, int>));

        map<int, int, less<int>, TrivialAllocator<pair<const int, int>>> m;

        for(int i = 1; i <= 10; ++i)
        {
            m[i * 2] = i * 2;
        }

        printf("\n\n\n");

        map<int, int, less<int>, TrivialAllocator<pair<const int, int>>> m2;

        m2 = m;
    }

    printf("\n\n\n");

    {
        unordered_map<int, int, hash<int>, equal_to<int>, TrivialAllocator<pair<const int, int>>> m;

        m[10] = 100;
        m[20] = 200;
        m[30] = 300;
    }
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
        for(int i=0;i<itemCount;++i)
        {
            m[i] = i;
        }

        for(int start = 0; start < step; ++start)
        {
            for(int i=start;i<itemCount;i+=step)
            {
                m.erase(i);
            }
        }

        MY_ASSERT(m.size() == 0);

        for(int start = 0; start < step; ++start)
        {
            for(int i=start;i<itemCount;i+=step)
            {
                m[i] = i;
            }
        }

        for(int i=0;i<itemCount;++i)
        {
            m.erase(i);
        }

        MY_ASSERT(m.size() == 0);
    }
}



void blockAllocatorTest()
{
    map<int, int, less<int>, BlockAllocator<pair<const int, int>>> m;

    m[10] = 100;
    m[20] = 200;
    m[30] = 300;

    //mapTest<map<int, int, less<int>, BlockAllocator<pair<const int, int>>>, 10>();
}

inline long long int getMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}



int main()
{
    //trivialAllocatorTest();
    //blockAllocatorTest();


    const int itemCount = 10000;
    const int iterationCount = 10;
    const int step = 100;

    long long int millis = getMilliseconds();
    mapInsertEraseTest<std::map<int,int>, itemCount, iterationCount, step>();
    std::cout << "default map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<map<int, int, less<int>, BlockAllocator<pair<const int, int>>>, itemCount, iterationCount, step>();
    std::cout << "block allocator map: " << getMilliseconds() - millis << std::endl;

    return 0;
}

