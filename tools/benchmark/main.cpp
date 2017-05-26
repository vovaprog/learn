#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <Tools.h>
#include <BenchmarkMap.h>


bool ResultToFile(const std::vector<BenchmarkParameters> & results, const char *benchSetName)
{
    std::string fileName("./plots/");

    boost::filesystem::create_directory(fileName);

    fileName = fileName + benchSetName;

    boost::filesystem::create_directory(fileName);

    fileName = fileName + "/" + results[0].testName + ".txt";

    std::ofstream fl;
    fl.open(fileName);

    for(const BenchmarkParameters &r : results)
    {
        fl << r.itemCount << "|" << r.ticks << std::endl;
    }

    return true;
}


template <bool (*Fun)(BenchmarkParameters &params)>
bool runBenchmark(std::vector<BenchmarkParameters> &paramVec, const char *benchSetName)
{
    for(BenchmarkParameters &params : paramVec)
    {
        if(!Fun(params))
        {
            std::cout << "benchmark failed" << std::endl;
            return false;
        }
    }

    ResultToFile(paramVec, benchSetName);

    return true;
}


bool randomVector(std::vector<uint64_t> &keys, int64_t itemCount)
{
    keys.clear();

    std::set<uint64_t> s;

    for(int i = 0; i < itemCount; ++i)
    {
        int k;
        for(k = 0; k < 1000; ++k)
        {
            uint64_t key = randomUInt64();
            if(s.count(key) == 0)
            {
                keys.push_back(key);
                s.insert(key);
                break;
            }
        }
        if(k == 1000)
        {
            return false;
        }
    }
    if((int64_t)keys.size() != itemCount || (int64_t)s.size() != itemCount)
    {
        return false;
    }
    return true;
}

bool createBenchmarkParameters(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep,
                               int64_t iterCount,
                               std::vector<BenchmarkParameters> &paramVec,
                               std::vector<uint64_t> &keys)
{
    paramVec.clear();
    paramVec.reserve(itemCountEnd);

    if(!randomVector(keys, itemCountEnd))
    {
        std::cout << "randomVector failed\n";
        return false;
    }

    for(int i = itemCountStart; i <= itemCountEnd; i += itemCountStep)
    {
        BenchmarkParameters params;
        params.itemCount = i;
        params.iterCount = iterCount;
        params.arg0 = &keys;

        paramVec.push_back(params);
    }

    return true;
}


bool benchMapsFind(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    std::vector<BenchmarkParameters> paramVec;
    std::vector<uint64_t> keys;

    const int64_t iterCount = 100000;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep, iterCount, paramVec, keys))
    {
        return false;
    }

    std::string benchSetName = "map find " + std::to_string(itemCountEnd);

    if(!runBenchmark<benchStdMapFind>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostMapFind>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchStdUnorderedMapFind>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostUnorderedMapFind>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchSortedVector>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchSortedDeque>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostFlatMapFind>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    return true;
}


bool benchMapsInsert(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    std::vector<BenchmarkParameters> paramVec;
    std::vector<uint64_t> keys;

    const int64_t iterCount = 100000;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep, iterCount, paramVec, keys))
    {
        return false;
    }

    std::string benchSetName = "map insert " + std::to_string(itemCountEnd);

    if(!runBenchmark<benchStdMapInsert>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostMapInsert>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchStdUnorderedMapInsert>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostUnorderedMapInsert>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostFlatMapFill>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    return true;
}


int main()
{
    //benchMapsFind(5, 350, 1);
    benchMapsFind(50, 3500, 30);
    //benchMapsFind(1000, 100000, 5000);

    //benchMapsInsert(5, 10000, 10);

    return 0;
}


