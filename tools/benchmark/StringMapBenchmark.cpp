#include <StringMapBenchmark.h>

#include <iostream>
#include <map>
#include <string.h>

struct CharPointerCompare
{
   bool operator()(const char *a, const char *b)
   {
      return strcmp(a, b) < 0;
   }
};

bool benchStringMapFind(BenchmarkParameters &params)
{
    std::vector<const char*> &keys = *static_cast<std::vector<const char *> *>(params.arg0);

    std::map<const char*, Data, CharPointerCompare> m;

    for(int i=0;i<params.itemCount;++i)
    {
        m[keys[i]] = Data();
    }

    if((int64_t)m.size() != params.itemCount)
    {
        return false;
    }

    int64_t searchCounter = 0;

    uint64_t ticks = getTicks();

    //=======================================================================

    while(searchCounter < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && searchCounter < params.iterCount; ++i, ++searchCounter)
        {
            auto iter = m.find(keys[i]);

            if(iter == m.end())
            {
                return false;
            }
        }
    }

    //=======================================================================

    params.ticks = getTicks() - ticks;

    params.testName = "string map find";

    return true;
}


bool createBenchmarkParameters(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep,
                               int64_t keyLength,
                               int64_t iterCount,
                               BenchmarkSet &benchSet,
                               std::vector<std::string> &keyStrings,
                               std::vector<const char*> &keyPointers)
{
    keyPointers.clear();

    if(!randomVector(keyStrings, itemCountEnd, keyLength))
    {
        return false;
    }

    for(std::string &s : keyStrings)
    {
        keyPointers.push_back(s.c_str());
    }

    if((int64_t)keyPointers.size() != itemCountEnd)
    {
        return false;
    }

    benchSet.params.clear();

    for(int i = itemCountStart; i <= itemCountEnd; i += itemCountStep)
    {
        BenchmarkParameters params;
        params.itemCount = i;
        params.iterCount = iterCount;
        params.arg0 = &keyPointers;

        benchSet.params.push_back(params);
    }

    return true;
}


bool benchStringMapFind(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep,
                         int64_t keyLength)
{
    const int64_t iterCount = 100000;

    BenchmarkSet benchSet;
    std::vector<std::string> keyStrings;
    std::vector<const char*> keyPointers;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep, keyLength,
                                  iterCount, benchSet, keyStrings, keyPointers))
    {
        return false;
    }

    benchSet.prefixes.push_back("string map find");
    benchSet.prefixes.push_back(std::to_string(itemCountEnd));


    if(!runBenchmarkSet<benchStringMapFind>(benchSet))
    {
        return false;
    }

    return true;
}


bool benchStringMapFind()
{
    if(!benchStringMapFind(10, 100, 1, 4))
    {
        return false;
    }

    return true;
}
