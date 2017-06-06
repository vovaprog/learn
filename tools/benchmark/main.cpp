#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <Tools.h>
#include <BenchmarkMap.h>
#include <IntrusiveMapBenchmark.h>
#include <ArithmeticBenchmark.h>
#include <StringMapBenchmark.h>


bool createBenchmarkParameters(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep,
                               int64_t iterCount,
                               BenchmarkSet &benchSet,
                               std::vector<uint64_t> &keys)
{
    if(!randomVector(keys, itemCountEnd))
    {
        std::cout << "randomVector failed\n";
        return false;
    }

    benchSet.params.clear();

    for(int i = itemCountStart; i <= itemCountEnd; i += itemCountStep)
    {
        BenchmarkParameters params;
        params.itemCount = i;
        params.iterCount = iterCount;
        params.arg0 = &keys;

        benchSet.params.push_back(params);
    }

    return true;
}


bool benchMapsFind(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    const int64_t iterCount = 100000;

    BenchmarkSet benchSet;
    std::vector<uint64_t> keys;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep,
                                  iterCount, benchSet, keys))
    {
        return false;
    }

    benchSet.prefixes.push_back("map find");
    benchSet.prefixes.push_back(std::to_string(itemCountEnd));


    if(!runBenchmarkSet<benchStdMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchStdUnorderedMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostUnorderedMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchSortedVector>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchSortedDeque>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostFlatMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchIntrusiveSetFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchIntrusiveAvlSetFind>(benchSet))
    {
        return false;
    }

    return true;
}


bool benchMapsInsert(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    const int64_t iterCount = 100000;

    BenchmarkSet benchSet;
    std::vector<uint64_t> keys;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep,
                                  iterCount, benchSet, keys))
    {
        return false;
    }

    benchSet.prefixes.push_back("map insert");
    benchSet.prefixes.push_back(std::to_string(itemCountEnd));

    if(!runBenchmarkSet<benchStdMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchStdUnorderedMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostUnorderedMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmarkSet<benchBoostFlatMapFill>(benchSet))
    {
        return false;
    }

    return true;
}


int main()
{
    srand(time(nullptr));

    //benchMapsFind(5, 350, 1);
    //benchMapsFind(50, 3500, 30);
    //benchMapsFind(1000, 100000, 5000);

    //benchMapsInsert(5, 10000, 10);

    //arithmeticBenchmark();

    benchStringMapFind();

    return 0;
}


