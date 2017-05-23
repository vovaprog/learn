#ifndef BENCH_STD_MAP_H
#define BENCH_STD_MAP_H

#include <Tools.h>

bool benchStdMap(BenchmarkParameters &params);
bool benchBoostMap(BenchmarkParameters &params);
bool benchStdUnorderedMap(BenchmarkParameters &params);
bool benchBoostUnorderedMap(BenchmarkParameters &params);
bool benchSortedVector(BenchmarkParameters &params);

#endif
