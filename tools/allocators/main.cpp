#include <BlockAllocator.h>
#include <TrivialAllocator.h>

#include <list>
#include <map>
#include <unordered_map>

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

template<typename MapType, int itemCount>
void mapTest()
{
    MapType m;

    for(int i=0;i<itemCount;++i)
    {
        m[i] = i;
    }

    const int step = 5;

    for(int i=0;i<itemCount;i+=step)
    {
        m.erase(i);
    }
}



void blockAllocatorTest()
{
    map<int, int, less<int>, BlockAllocator<pair<const int, int>>> m;

    m[10] = 100;
    m[20] = 200;
    m[30] = 300;

    mapTest<map<int, int, less<int>, BlockAllocator<pair<const int, int>>>, 10>();
}




int main()
{
    trivialAllocatorTest();
    blockAllocatorTest();

    return 0;
}

