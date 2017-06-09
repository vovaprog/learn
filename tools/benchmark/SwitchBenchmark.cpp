#include <SwitchBenchmark.h>
#include <Tools.h>
#include <SwitchBenchmarkGen.cpp>

#include <map>
#include <unordered_map>

bool runSwitch(BenchmarkParameters &params, int testIndex)
{
    SwitchFunction switchFun = switchFuns[testIndex];

    int count = 0;

    uint64_t ticks = getTicks();

    while(count < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && count < params.iterCount; ++i, ++count)
        {
            if(switchFun(keys[i]) != vals[i])
            {
                return false;
            }
        }
    }

    params.ticks = getTicks() - ticks;

    return true;
}


template<typename MapType>
bool runMap(BenchmarkParameters &params)
{
    MapType m;

    for(int i=0;i<params.itemCount; ++i)
    {
        m[keys[i]] = vals[i];
    }

    int count = 0;

    uint64_t ticks = getTicks();

    while(count < params.iterCount)
    {
        for(int i = 0; i < params.itemCount && count < params.iterCount; ++i, ++count)
        {
            if(m[keys[i]] != vals[i])
            {
                return false;
            }
        }
    }

    params.ticks = getTicks() - ticks;

    return true;
}

bool switchBenchmark()
{
    const int iterCount = 10000000;

    {
        BenchmarkSet bs;

        bs.prefixes.push_back("switch");

        for(size_t i = 0; i < funCount; ++i)
        {
            BenchmarkParameters params;
            params.itemCount = counts[i];
            params.iterCount = iterCount;
            params.testName = "switch";

            runSwitch(params, i);

            bs.params.push_back(params);
        }

        ResultToFile(bs);
    }

    {
        BenchmarkSet bs;

        bs.prefixes.push_back("switch");

        for(size_t i = 0; i < funCount; ++i)
        {
            BenchmarkParameters params;
            params.itemCount = counts[i];
            params.iterCount = iterCount;
            params.testName = "map";

            runMap<std::map<uint32_t, uint32_t>>(params);

            bs.params.push_back(params);
        }

        ResultToFile(bs);
    }


    {
        BenchmarkSet bs;

        bs.prefixes.push_back("switch");

        for(size_t i = 0; i < funCount; ++i)
        {
            BenchmarkParameters params;
            params.itemCount = counts[i];
            params.iterCount = iterCount;
            params.testName = "unordered_map";

            runMap<std::unordered_map<uint32_t, uint32_t>>(params);

            bs.params.push_back(params);
        }

        ResultToFile(bs);
    }

    return true;
}



