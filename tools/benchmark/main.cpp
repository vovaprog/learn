#include <stdlib.h>

#include <MapBenchmark.h>
#include <IntrusiveMapBenchmark.h>
#include <ArithmeticBenchmark.h>
#include <StringMapBenchmark.h>
#include <SwitchBenchmark.h>


int main()
{
    srand(time(nullptr));

    mapFindBenchmark();
    mapInsertBenchmark();
    arithmeticBenchmark();
    stringMapFindBenchmark();
    switchBenchmark();

    return 0;
}


