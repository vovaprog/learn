#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <cstdint>
#include <chrono>
#include <random>

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

struct BenchmarkParameters {
    int64_t itemCount = 0;
    int64_t iterCount = 0;
    uint64_t ticks = 0;
    void *arg0 = nullptr;
    const char * testName = nullptr;
};

#endif

