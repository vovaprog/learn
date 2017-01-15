#include <TrivialAllocator.h>

#include <list>
#include <map>
#include <unordered_map>

using namespace std;

int main()
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
        unordered_map<int, int, hash<int>, equal_to<int>, TrivialAllocator<pair<const int, int>>> m3;

        m3[10] = 100;
        m3[20] = 200;
        m3[30] = 300;
    }

    return 0;
}

