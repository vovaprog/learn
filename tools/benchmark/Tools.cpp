#include <Tools.h>

#include <set>
#include <fstream>
#include <boost/filesystem.hpp>

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


bool resultToFile(const BenchmarkSingle &bench)
{
    std::string fileName("./plots");

    boost::filesystem::create_directory(fileName);

    for(auto &prefix : bench.prefixes)
    {
        fileName = fileName + "/" + prefix;
        boost::filesystem::create_directory(fileName);
    }

    fileName = fileName + "/" + bench.params.testName + ".txt";

    std::ofstream fl;
    fl.open(fileName);

    fl << bench.params.ticks << std::endl;

    return true;
}

