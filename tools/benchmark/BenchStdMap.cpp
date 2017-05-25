#include <BenchStdMap.h>

#include <Tools.h>

#include <map>
#include <unordered_map>
#include <boost/container/map.hpp>
#include <boost/unordered_map.hpp>

namespace
{

struct Data
{
    uint64_t key;
    uint64_t a, b, c, d;
};

}


template<typename MapType>
bool benchMap(BenchmarkParameters &params)
{
    MapType m;

    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    for(int i = 0; i < params.itemCount; ++i)
    {
        Data d;
        d.key = keys[i];
        m[d.key] = d;
    }

    int64_t searchCounter = 0;

    uint64_t ticks = getTicks();

    //=======================================================================

    while(searchCounter < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && searchCounter < params.iterCount; ++i, ++searchCounter)
        {
            if(m.find(keys[i]) == m.end())
            {
                return false;
            }
        }
    }

    //=======================================================================

    params.ticks = getTicks() - ticks;

    return true;
}


bool benchStdMap(BenchmarkParameters &params)
{
    bool result = benchMap<std::map<uint64_t, Data>>(params);
    params.testName = "std map find";
    return result;
}


bool benchBoostMap(BenchmarkParameters &params)
{
    bool result = benchMap<boost::container::map<uint64_t, Data>>(params);
    params.testName = "boost map find";
    return result;
}


bool benchStdUnorderedMap(BenchmarkParameters &params)
{
    bool result = benchMap<std::unordered_map<uint64_t, Data>>(params);
    params.testName = "std unordered_map find";
    return result;
}


bool benchBoostUnorderedMap(BenchmarkParameters &params)
{
    bool result = benchMap<boost::unordered_map<uint64_t, Data>>(params);
    params.testName = "boost unordered_map find";
    return result;
}


bool benchSortedVector(BenchmarkParameters &params)
{
    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    std::vector<Data> v;

    for(int i = 0; i < params.itemCount; ++i)
    {
        Data d;
        d.key = keys[i];
        v.push_back(d);
    }

    std::sort(v.begin(), v.end(),
              [](const Data & d0, const Data & d1)
    {
        return d0.key < d1.key;
    });

    int64_t searchCounter = 0;

    uint64_t ticks = getTicks();

    //=======================================================================

    while(searchCounter < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && searchCounter < params.iterCount; ++i, ++searchCounter)
        {
            auto iter = std::lower_bound(v.begin(), v.end(), keys[i],
                                         [](const Data & d, uint64_t key)
            {
                return d.key < key;
            });

            if(iter == v.end() || iter->key != keys[i])
            {
                return false;
            }
        }
    }

    //=======================================================================

    params.ticks = getTicks() - ticks;
    params.testName = "std vector find";

    return true;
}

