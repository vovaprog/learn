#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <cstdint>
#include <chrono>
#include <random>
#include <iostream>
#include <limits>


inline uint64_t getTicks()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}


inline uint64_t randomUInt64()
{
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dis;
    return dis(gen);
}


template<typename T>
T randomValue()
{
    return static_cast<T>(randomUInt64());
}


struct BenchmarkParameters
{
    int64_t itemCount = 0;
    int64_t iterCount = 0;
    uint64_t ticks = 0;
    void *arg0 = nullptr;
    const char * testName = nullptr;
};


struct BenchmarkSet
{
    std::vector<BenchmarkParameters> params;
    std::vector<std::string> prefixes;
};


struct BenchmarkSingle
{
    BenchmarkParameters params;
    std::vector<std::string> prefixes;
};


bool randomVector(std::vector<uint64_t> &keys, int64_t itemCount);


bool resultToFile(const BenchmarkSingle &bench);


#endif

