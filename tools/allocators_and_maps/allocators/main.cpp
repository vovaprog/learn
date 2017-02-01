#include <BlockAllocator.h>
#include <TrivialAllocator.h>

#include <MapTests.h>

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

void mapInsertEraseTestFull()
{
    cout << "======= InsertEraseTest =======" << endl;

    const int itemCount = 100000;
    const int iterationCount = 10;
    const int step = 100;

    long long int millis = getMilliseconds();
    mapInsertEraseTest<std::map<int, int>, itemCount, iterationCount, step>();
    std::cout << "default map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<map<int, int, less<int>, BlockAllocator<pair<const int, int>>>, itemCount, iterationCount, step>();
    std::cout << "block allocator map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<std::unordered_map<int, int>, itemCount, iterationCount, step>();
    std::cout << "unordered map: " << getMilliseconds() - millis << std::endl;
}


void searchTestFull()
{
    cout << "======= SearchTest =======" << endl;

    const int itemCount = 100000;
    const int iterCount = 5;
    const int keyLength = 15;

    vector<string> randStrings;
    randStrings.reserve(itemCount);

    for(int i = 0; i < itemCount; ++i)
    {
        std::string key = generateRandomString<keyLength>();
        randStrings.push_back(key);
    }

    searchTest<std::map<string, string>, iterCount>("std map", randStrings);
    searchTest<std::map<string, string, less<string>, BlockAllocator<pair<const string, string> >>, iterCount>("block allocator std map", randStrings);
    searchTest<std::unordered_map<string, string>, iterCount>("std unordered_map", randStrings);
}



int main()
{
    srand(time(NULL));

    trivialAllocatorTest();
    mapInsertEraseTestFull();
    searchTestFull();

    return 0;
}
