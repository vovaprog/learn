#include <iostream>
#include <sys/time.h>
#include <iostream>
#include <atomic>

#define DEBUG_THREAD_POOL
#include "thread_pool_spsc.h"
#include "thread_pool_locked.h"

using namespace std;


int keyResults[1000000] = {0};

long long int getMilliseconds()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}



class TaskKeyCounters
{
public:
	TaskKeyCounters(): key(0) {}
	TaskKeyCounters(int k): key(k) {}
	int getKey()
	{
		return key;
	}
	void execute()
	{
		++keyResults[key];
		for (int i = 0; i < 1000000; ++i)
			if (i == 1000) cout << "";
	}
private:
	int key;
};

template<template<class> class ThreadPool, class Task>
void testKeyCounters(int numberOfThreads, int numberOfKeys, int numberOfTasks)
{
	if (numberOfTasks % numberOfKeys != 0)
		throw std::logic_error("test 1: invalid numberOfTasks!");

	for (int i = 0; i < numberOfKeys; ++i)
		keyResults[i] = 0;



	long long int start = getMilliseconds();

	{
		ThreadPool<Task> pool;

		pool.init(numberOfThreads, numberOfKeys, 100000);

		for (int i = 0; i < numberOfTasks; ++i) {
			Task t(i % numberOfKeys);
			while (pool.enqueue(t));
		}
	}

	long long int dif = getMilliseconds() - start;



	for (int i = 0; i < numberOfKeys; ++i) {
		if (keyResults[i] != numberOfTasks / numberOfKeys) {
			cerr << "invalid result[" << i << "] = " << keyResults[i] << endl;
			throw std::logic_error("test 1: invalid result!");
		}
	}

	std::cout << "threads: " << numberOfThreads << "   keys: " << numberOfKeys << "   time: " << dif << std::endl;
}




atomic_int execCounter(0);

class TaskCountTotal
{
public:
	TaskCountTotal(): key(0) {}
	TaskCountTotal(int k): key(k) {}
	int getKey()
	{
		return key;
	}
	void execute()
	{
		++execCounter;
	}
private:
	int key;
};

template<template<class> class ThreadPool, class Task>
void testCountTotal(int numberOfThreads, int numberOfKeys, int numberOfTasks)
{
	execCounter.store(0);

	{
		ThreadPool<Task> pool;
		pool.init(numberOfThreads, numberOfKeys, 10000);

		for (long long int i = 0; i < numberOfTasks; ++i) {
			Task t(i % numberOfKeys);
			while (pool.enqueue(t) != 0);
		}
	}

	if (execCounter.load() != numberOfTasks) {
		throw std::logic_error("test4: invalid exec count!");
	}
}




class TaskPrintChars
{
public:
	TaskPrintChars(): key(0) {}
	TaskPrintChars(int k): key(k) {}
	int getKey()
	{
		return key;
	}
	void execute()
	{
		cout << (char)('a' + key) << flush;
	}
private:
	int key;
};

template<template<class> class ThreadPool, class Task>
void testPrintChars(int numberOfThreads, int numberOfKeys)
{
	ThreadPool<Task> pool;

	pool.init(numberOfThreads, numberOfKeys, 10000);

	for (long long int i = 0; ; ++i) {
		Task t(i % numberOfKeys);
		if (pool.enqueue(t) != 0) {
			cout << "!" << flush;
		} else {
			cout << "-" << flush;
		}

		if (i % 100 == 0) {
			int totalQSize = pool.totalQueueSize();
			cout << endl << "[" << totalQSize << "]" << endl;
		}
	}
}




int execCounterPrev = 0;
long long int millisPrev = 0;

class TaskExecPerSecond
{
public:
	TaskExecPerSecond(): key(0) { }
	TaskExecPerSecond(int k): key(k) {}
	int getKey()
	{
		return key;
	}
	void execute()
	{
		++execCounter;
	}
private:
	int key;
};

template<template<class> class ThreadPool, class Task>
void testExecPerSecond(int numberOfThreads, int numberOfKeys)
{
	ThreadPool<Task> pool;

	pool.init(numberOfThreads, numberOfKeys, 10000);

	for (long long int i = 0; ; ++i) {
		Task t(i % numberOfKeys);
		pool.enqueue(t);

		if (i % 100000 == 0) {
			int execCounterCur = execCounter.load();
			int millisCur = getMilliseconds();

			if (execCounterPrev != 0) {
				int counterDif = execCounterCur - execCounterPrev;
				long long int millisDif = millisCur - millisPrev;

				long long int execPerSec = (counterDif / millisDif) * 1000;

				cout << "exec per sec: " << execPerSec << "" << endl;
			}

			execCounterPrev = execCounterCur;
			millisPrev = millisCur;
		}
	}
}



int main()
{
	/*testKeyCounters(1, 1000, 10000);
	testKeyCounters(2, 1000, 10000);
	testKeyCounters(4, 1000, 10000);
	testKeyCounters(8, 1000, 10000);
	testKeyCounters(10, 1000, 10000);
	testKeyCounters(12, 1000, 10000);
	testKeyCounters(20, 1000, 10000);
	testKeyCounters(50, 1000, 10000);

	testKeyCounters(12, 4, 10000);
	testKeyCounters(12, 10, 10000);
	testKeyCounters(12, 100, 10000);
	testKeyCounters(12, 10000, 10000);


	testCountTotal(1, 1000, 100000);
	testCountTotal(8, 1000, 100000);
	testCountTotal(20, 1000, 100000);
	testCountTotal(50, 1000, 100000);*/


	testPrintChars<ThreadPoolSpsc, TaskPrintChars>(8, 26);
	//testExecPerSecond<ThreadPoolSpsc, TaskExecPerSecond>(8, 26);
	//testExecPerSecond<ThreadPoolLocked, TaskExecPerSecond>(8, 26);

	return 0;
}

