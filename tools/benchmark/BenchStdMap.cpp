#include <BenchStdMap.h>

#include <Tools.h>

#include <map>
#include <unordered_map>

namespace {

struct Data {
    uint64_t key;
    uint64_t a, b, c, d;
};

}

template<typename MapType>
bool benchMap(BenchmarkParameters &params)
{
    MapType m;

    std::vector<uint64_t> &keys = *reinterpret_cast<std::vector<uint64_t>*>(params.arg0);

    for(int i=0;i<params.itemCount;++i)
    {
        Data d;
        d.key = keys[i];
        m[d.key] = d;
    }

    uint64_t ticks = getTicks();

    for(int i=0;i<params.itemCount;++i)
    {
        if(m.find(keys[i]) == m.end())
        {
            return false;
        }
    }

    params.ticks = getTicks() - ticks;

    return true;
}


bool benchStdMap(BenchmarkParameters &params)
{
    return benchMap<std::map<uint64_t, Data>>(params);
}

bool benchStdUnorderedMap(BenchmarkParameters &params)
{
    return benchMap<std::unordered_map<uint64_t, Data>>(params);
}


