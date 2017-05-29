#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <Tools.h>
#include <BenchmarkMap.h>


bool ResultToFile(const BenchmarkSet &benchSet)
{
    std::string fileName("./plots");

    boost::filesystem::create_directory(fileName);

    for(auto &prefix : benchSet.prefixes)
    {
        fileName = fileName + "/" + prefix;
        boost::filesystem::create_directory(fileName);
    }

    fileName = fileName + "/" + benchSet.params[0].testName + ".txt";

    std::ofstream fl;
    fl.open(fileName);

    for(const BenchmarkParameters &r : benchSet.params)
    {
        fl << r.itemCount << "|" << r.ticks << std::endl;
    }

    return true;
}


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


// copy of benchSet is created in argument
template <bool (*Fun)(BenchmarkParameters &params)>
bool runBenchmark(BenchmarkSet benchSet)
{
    for(BenchmarkParameters &params : benchSet.params)
    {
        if(!Fun(params))
        {
            std::cout << "benchmark failed" << std::endl;
            return false;
        }
    }

    ResultToFile(benchSet);

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


    if(!runBenchmark<benchStdMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchStdUnorderedMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostUnorderedMapFind>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchSortedVector>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchSortedDeque>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostFlatMapFind>(benchSet))
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

    if(!runBenchmark<benchStdMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchStdUnorderedMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostUnorderedMapInsert>(benchSet))
    {
        return false;
    }

    if(!runBenchmark<benchBoostFlatMapFill>(benchSet))
    {
        return false;
    }

    return true;
}


int main()
{
    benchMapsFind(5, 350, 1);
    //benchMapsFind(50, 3500, 30);
    //benchMapsFind(1000, 100000, 5000);

    benchMapsInsert(5, 10000, 10);

    return 0;
}


