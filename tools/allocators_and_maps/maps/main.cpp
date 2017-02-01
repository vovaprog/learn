#include <string>
#include <iostream>

#include <EASTL/map.h>
#include <EASTL/fixed_map.h>

#include <google/sparse_hash_map>

#include <MapTests.h>

using namespace std;


void mapInsertEraseTestFull()
{
    cout << "======= InsertEraseTest =======" << endl;

    const int itemCount = 1000000;
    const int iterationCount = 1;
    const int step = 100;

    long long int millis = getMilliseconds();
    mapInsertEraseTest<std::map<int, int>, itemCount, iterationCount, step>();
    std::cout << "default map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<eastl::map<int, int>, itemCount, iterationCount, step>();
    std::cout << "eastl map: " << getMilliseconds() - millis << std::endl;

    millis = getMilliseconds();
    mapInsertEraseTest<std::unordered_map<int, int>, itemCount, iterationCount, step>();
    std::cout << "unordered map: " << getMilliseconds() - millis << std::endl;    
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


void searchTestFull()
{
    cout << "======= SearchTest =======" << endl;

    const int itemCount = 1000000;
    const int iterCount = 1;
    const int keyLength = 15;

    vector<string> randStrings;
    randStrings.reserve(itemCount);

    for(int i = 0; i < itemCount; ++i)
    {
        std::string key = generateRandomString<keyLength>();
        randStrings.push_back(key);
    }

    searchTest<std::map<string, string>, iterCount>("std map", randStrings);
    searchTest<eastl::map<std::string, std::string>, iterCount>("eastl map", randStrings);
    searchTest<std::unordered_map<string, string>, iterCount>("std unordered_map", randStrings);
    searchTest<google::sparse_hash_map<string, string>, iterCount>("google sparse_hash_map", randStrings);
}

int main()
{
	mapInsertEraseTestFull();
	searchTestFull();	
}
