#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/intrusive/list.hpp>
#include <boost/filesystem.hpp>

#include <MapBenchmark.h>
#include <IntrusiveMapBenchmark.h>
#include <ArithmeticBenchmark.h>
#include <StringMapBenchmark.h>


int main()
{
    srand(time(nullptr));

    /*benchmarkMapFind();
    benchmarkMapInsert();
    arithmeticBenchmark();*/
    benchStringMapFind();

    return 0;
}


