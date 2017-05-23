#include <iostream>
#include <fstream>
#include <vector>
#include <boost/intrusive/list.hpp>

#include <Tools.h>
#include <BenchStdMap.h>

using namespace std;

/*bool runBenchmark(BenchmarkParameters &params)
{
    if(!benchStdMap(params))
    {
        return false;
    }

    return true;
}*/

template <bool (*Fun)(BenchmarkParameters &params)>
bool runBenchmark(std::vector<BenchmarkParameters> &paramsVec)
{
    for(BenchmarkParameters &params : paramsVec)
    {
        if(!Fun(params))
        {
            return false;
        }
    }
    return true;
}

bool ResultToFile(const std::vector<BenchmarkParameters> & results)
{
    std::string fileName("./");
    fileName = fileName + results[0].testName + ".txt";

    std::ofstream fl;
    fl.open(fileName);

    for(const BenchmarkParameters &r : results)
    {
        fl << r.itemCount << "|" << r.ticks << std::endl;
    }

    return true;
}

int main()
{    
    std::vector<BenchmarkParameters> paramVec;

    int start = 1000;
    int end = 100000;
    int step = 10000;

    std::vector<uint64_t> keys;
    keys.reserve(end);

    for(int i=0;i<end;++i)
    {
        keys.push_back(randomUInt64());
    }

    for(int i = start; i <= end; i+=step)
    {
        BenchmarkParameters params;
        params.itemCount = i;
        params.arg0 = &keys;

        paramVec.push_back(params);
    }

    if(!runBenchmark<benchStdMap>(paramVec))
    {
        std::cout << "benchmark failed" << std::endl;
        return -1;
    }

    ResultToFile(paramVec);

    if(!runBenchmark<benchBoostMap>(paramVec))
    {
        std::cout << "benchmark failed" << std::endl;
        return -1;
    }

    ResultToFile(paramVec);


    if(!runBenchmark<benchStdUnorderedMap>(paramVec))
    {
        std::cout << "benchmark failed" << std::endl;
        return -1;
    }

    ResultToFile(paramVec);

    if(!runBenchmark<benchBoostUnorderedMap>(paramVec))
    {
        std::cout << "benchmark failed" << std::endl;
        return -1;
    }

    ResultToFile(paramVec);

    return 0;
}


