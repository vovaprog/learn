#include <Tools.h>

template<typename T, long long int iterCount>
struct OperationAdd {
    static T __attribute__((optimize("O0"))) calculate(int x, int inc)
    {
        T result;
        for(int i=0;i<iterCount;++i)
        {
            result = x + inc;
        }
        return result;
    }
};

template<typename T, long long int iterCount>
struct OperationMul {
    static T __attribute__((optimize("O0"))) calculate(int x, int inc)
    {
        T result;
        for(int i=0;i<iterCount;++i)
        {
            result = x * inc;
        }
        return result;
    }
};

template<typename Operation, typename T>
void run(BenchmarkParameters &params)
{
    T x = randomValue<T>();
    T inc = randomValue<T>() % 10 + 2;

    uint64_t ticks = getTicks();

    x = Operation::calculate(x, inc);
    useValue(x);

    params.ticks = getTicks() - ticks;
}


void benchAdd()
{
    const long long int iterCount = 10000;

    run<OperationAdd<int, iterCount>, int>(params);
    run<OperationAdd<long long int, iterCount>, long long int>(params);
}


