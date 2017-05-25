#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <Tools.h>
#include <BenchStdMap.h>


bool ResultToFile(const std::vector<BenchmarkParameters> & results, const char *benchSetName)
{
    std::string fileName("./plots/");

    boost::filesystem::create_directory(fileName);

    fileName = fileName + benchSetName;

    if(!boost::filesystem::is_directory(fileName))
    {
        boost::filesystem::create_directory(fileName);
    }

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


bool benchMaps(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    std::vector<BenchmarkParameters> paramVec;
    std::vector<uint64_t> keys;

    const int64_t iterCount = 100000;

    if(!createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep, iterCount, paramVec, keys))
    {
        return false;
    }

    std::string benchSetName = std::to_string(itemCountEnd);

    if(!runBenchmark<benchStdMap>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostMap>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchStdUnorderedMap>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchBoostUnorderedMap>(paramVec, benchSetName.c_str()))
    {
        return false;
    }

    if(!runBenchmark<benchSortedVector>(paramVec, benchSetName.c_str()))
    {
        return -1;
    }

    return true;
}

int main()
{
    //benchMaps(5, 350, 1);
    benchMaps(50, 3000, 20);
    //benchMaps(1000, 100000, 5000);

    return 0;
}


