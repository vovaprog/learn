#ifndef BENCHMARK_MAP_H
#define BENCHMARK_MAP_H

#include <Tools.h>

bool benchStdMapFind(BenchmarkParameters &params);
bool benchBoostMapFind(BenchmarkParameters &params);
bool benchStdUnorderedMapFind(BenchmarkParameters &params);
bool benchBoostUnorderedMapFind(BenchmarkParameters &params);

bool benchBoostFlatMapFind(BenchmarkParameters &params);
bool benchSortedVector(BenchmarkParameters &params);
bool benchSortedDeque(BenchmarkParameters &params);

bool benchStdMapInsert(BenchmarkParameters &params);
bool benchBoostMapInsert(BenchmarkParameters &params);
bool benchStdUnorderedMapInsert(BenchmarkParameters &params);
bool benchBoostUnorderedMapInsert(BenchmarkParameters &params);
bool benchBoostFlatMapFill(BenchmarkParameters &params);

#endif
