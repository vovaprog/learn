#include <iostream>
#include <fstream>
#include <vector>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <Tools.h>
#include <BenchStdMap.h>

using namespace std;


bool ResultToFile(const std::vector<BenchmarkParameters> & results, const char *benchSetName)
{
    std::string fileName("./plots/");

    if(!boost::filesystem::is_directory(fileName))
    {
        boost::filesystem::create_directory(fileName);
    }

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


void createBenchmarkParameters(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep,
                               int64_t iterCount,
                               std::vector<BenchmarkParameters> &paramVec,
                               std::vector<uint64_t> &keys)
{
    paramVec.clear();
    keys.clear();

    paramVec.reserve(itemCountEnd);
    keys.reserve(itemCountEnd);

    for(int i = 0; i < itemCountEnd; ++i)
    {
        keys.push_back(randomUInt64());
    }

    for(int i = itemCountStart; i <= itemCountEnd; i += itemCountStep)
    {
        BenchmarkParameters params;
        params.itemCount = i;
        params.iterCount = iterCount;
        params.arg0 = &keys;

        paramVec.push_back(params);
    }
}


bool benchMaps(int64_t itemCountStart, int64_t itemCountEnd, int64_t itemCountStep)
{
    std::vector<BenchmarkParameters> paramVec;
    std::vector<uint64_t> keys;

    const int64_t iterCount = 100000;

    createBenchmarkParameters(itemCountStart, itemCountEnd, itemCountStep, iterCount, paramVec, keys);

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
    benchMaps(5, 250, 1);
    benchMaps(50, 1000, 10);
    //benchMaps(1000, 100000, 5000);

    return 0;
}


