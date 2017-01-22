#include <BlockAllocator.h>
#include <TrivialAllocator.h>

#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>

#include <EASTL/map.h>
#include <EASTL/fixed_map.h>

using namespace std;


inline long long int getMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}


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


void mapInsertEraseTestFull()
{
    const int itemCount = 10000;
    const int iterationCount = 100;
    const int step = 100;

    long long int millis = getMilliseconds();
    mapInsertEraseTest<std::map<int,int>, itemCount, iterationCount, step>();
    std::cout << "default map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<map<int, int, less<int>, BlockAllocator<pair<const int, int>>>, itemCount, iterationCount, step>();
    std::cout << "block allocator map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<eastl::map<int,int>, itemCount, iterationCount, step>();
    std::cout << "eastl map: " << getMilliseconds() - millis << std::endl;
}


template<int stringLength>
std::string generateRandomString()
{
    char buf[stringLength+1];

    for(int i=0;i<stringLength;++i)
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

        for(int q = 0;q<iterCount;++q)
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


void searchTestFull()
{
    const int itemCount = 100000;
    const int iterCount = 5;
    const int keyLength = 15;

    vector<string> randStrings;
    randStrings.reserve(itemCount);

    for(int i=0;i<itemCount;++i)
    {
        std::string key = generateRandomString<keyLength>();
        randStrings.push_back(key);
    }

    searchTest<std::map<string, string>, iterCount>("std map", randStrings);
    searchTest<std::map<string, string, less<string>, BlockAllocator<pair<const string, string> >>, iterCount>("block allocator std map", randStrings);
    searchTest<eastl::map<std::string, std::string>, iterCount>("eastl map", randStrings);
    searchTest<std::unordered_map<string, string>, iterCount>("std unordered_map", randStrings);
}

// new operators for eastl
void* operator new[](size_t size, const char* /*name*/, int /*flags*/,
                     unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) // THROW_SPEC_1(std::bad_alloc)
{
    return malloc(size);
}

// new operators for eastl
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* /*name*/,
                     int flags, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) //THROW_SPEC_1(std::bad_alloc)
{
    return aligned_alloc(alignment, size);
}


int main()
{
    srand (time(NULL));

    trivialAllocatorTest();
    mapInsertEraseTestFull();
    searchTestFull();

    return 0;
}

