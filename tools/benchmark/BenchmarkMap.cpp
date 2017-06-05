#include <BenchmarkMap.h>

#include <Tools.h>

#include <map>
#include <unordered_map>
#include <deque>
#include <boost/container/map.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>


template<typename MapType>
bool benchMapFind_fillMap(BenchmarkParameters &params, MapType &m)
{
    m.clear();

    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    for(int i = 0; i < params.itemCount; ++i)
    {
        Data d;
        d.key = keys[i];
        m[d.key] = d;
    }

    return true;
}


// fillMap specialization for boost::flat_map,
// needed because insertion into boost::flat_map is very slow.
template<>
bool benchMapFind_fillMap<boost::container::flat_map<uint64_t, Data>>(
            BenchmarkParameters &params, boost::container::flat_map<uint64_t, Data> &m)
{
    m.clear();

    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);
    std::vector<boost::container::flat_map<uint64_t, Data>::value_type> values;

    values.reserve(params.itemCount);

    for(int i = 0; i < params.itemCount; ++i)
    {
        Data d;
        d.key = keys[i];

        boost::container::flat_map<uint64_t, Data>::value_type p;
        p.first = keys[i];
        p.second = d;

        values.push_back(p);
    }

    m.reserve(params.itemCount);

    // values should be sorted before insertion
    std::sort(values.begin(), values.end(),
              [](boost::container::flat_map<uint64_t, Data>::value_type & v0,
                 boost::container::flat_map<uint64_t, Data>::value_type & v1)
    {
        return v0.first < v1.first;
    });

    // ordered_unique_range_t indicates that values are sorted and unique
    m.insert(boost::container::ordered_unique_range_t(), values.begin(), values.end());

    return true;
}


template<typename MapType>
bool benchMapFind(BenchmarkParameters &params)
{
    MapType m;

    if(!benchMapFind_fillMap(params, m))
    {
        return false;
    }

    if(m.size() != static_cast<uint64_t>(params.itemCount))
    {
        return false;
    }

    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    int64_t searchCounter = 0;

    uint64_t ticks = getTicks();

    //=======================================================================

    while(searchCounter < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && searchCounter < params.iterCount; ++i, ++searchCounter)
        {
            auto iter = m.find(keys[i]);

            if(iter == m.end() || iter->second.key != keys[i])
            {
                return false;
            }
        }
    }

    //=======================================================================

    params.ticks = getTicks() - ticks;

    return true;
}


bool benchStdMapFind(BenchmarkParameters &params)
{
    bool result = benchMapFind<std::map<uint64_t, Data>>(params);
    params.testName = "std map find";
    return result;
}


bool benchBoostMapFind(BenchmarkParameters &params)
{
    bool result = benchMapFind<boost::container::map<uint64_t, Data>>(params);
    params.testName = "boost map find";
    return result;
}


bool benchBoostFlatMapFind(BenchmarkParameters &params)
{
    bool result = benchMapFind<boost::container::flat_map<uint64_t, Data>>(params);
    params.testName = "boost flat_map find";
    return result;
}


bool benchStdUnorderedMapFind(BenchmarkParameters &params)
{
    bool result = benchMapFind<std::unordered_map<uint64_t, Data>>(params);
    params.testName = "std unordered_map find";
    return result;
}


bool benchBoostUnorderedMapFind(BenchmarkParameters &params)
{
    bool result = benchMapFind<boost::unordered_map<uint64_t, Data>>(params);
    params.testName = "boost unordered_map find";
    return result;
}


template<typename T>
bool benchSortedArray(BenchmarkParameters &params)
{
    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    T v;

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

    return true;
}


bool benchSortedVector(BenchmarkParameters &params)
{
    bool result = benchSortedArray<std::vector<Data>>(params);
    params.testName = "std vector find";
    return result;
}


bool benchSortedDeque(BenchmarkParameters &params)
{
    bool result = benchSortedArray<std::deque<Data>>(params);
    params.testName = "std deque find";
    return result;
}


template<typename MapType>
bool benchMapInsert(BenchmarkParameters &params)
{
    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    uint64_t ticks = getTicks();

    MapType m;

    //=======================================================================

    for(int i = 0; i < params.itemCount; ++i)
    {
        Data d;
        d.key = keys[i];
        m[d.key] = d;
    }

    //=======================================================================

    params.ticks = getTicks() - ticks;

    if(m.size() != static_cast<uint64_t>(params.itemCount))
    {
        return false;
    }

    return true;
}


bool benchStdMapInsert(BenchmarkParameters &params)
{
    bool result = benchMapInsert<std::map<uint64_t, Data>>(params);
    params.testName = "std map insert";
    return result;
}


bool benchBoostMapInsert(BenchmarkParameters &params)
{
    bool result = benchMapInsert<boost::container::map<uint64_t, Data>>(params);
    params.testName = "boost map insert";
    return result;
}


bool benchStdUnorderedMapInsert(BenchmarkParameters &params)
{
    bool result = benchMapInsert<std::unordered_map<uint64_t, Data>>(params);
    params.testName = "std unordered_map insert";
    return result;
}


bool benchBoostUnorderedMapInsert(BenchmarkParameters &params)
{
    bool result = benchMapInsert<boost::unordered_map<uint64_t, Data>>(params);
    params.testName = "boost unordered_map insert";
    return result;
}


bool benchBoostFlatMapFill(BenchmarkParameters &params)
{
    boost::container::flat_map<uint64_t, Data> m;

    uint64_t ticks = getTicks();

    bool result = benchMapFind_fillMap(params, m);

    params.ticks = getTicks() - ticks;

    if(m.size() != static_cast<uint64_t>(params.itemCount))
    {
        return false;
    }

    params.testName = "boost flat_map fill";
    return result;
}

