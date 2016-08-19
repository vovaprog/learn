#ifndef THREAD_POOL_SPSC_H
#define THREAD_POOL_SPSC_H

#include <climits>

#include "thread_pool_thread_spsc.h"


template<class Task>
class ThreadPoolSpsc
{
public:
	ThreadPoolSpsc() = default;

	ThreadPoolSpsc(const ThreadPoolSpsc &tm) = delete;
	ThreadPoolSpsc(ThreadPoolSpsc &&tm) = delete;
	ThreadPoolSpsc& operator=(const ThreadPoolSpsc &tm) = delete;
	ThreadPoolSpsc& operator=(ThreadPoolSpsc &&tm) = delete;


	~ThreadPoolSpsc()
	{
		if (dispThreads != nullptr) {
			delete[] dispThreads;
		}
	}


	int init(int numberOfThreads, int numberOfKeys, int maxQueueSize)
	{
		this->numberOfThreads = numberOfThreads;
		dispThreads = new ThreadPoolThreadSpsc<Task>[numberOfThreads];

		for (int i = 0; i < numberOfThreads; ++i) {
			dispThreads[i].init(numberOfKeys, maxQueueSize);
		}

		return 0;
	}


	bool isInited() const
	{
		return (dispThreads != nullptr);
	}

	int enqueue(Task t)
	{
		int minQueueSize = INT_MAX;
		int threadIndex = 0;

		for (int i = 0; i < numberOfThreads; ++i) {

			if (dispThreads[i].inWork(t.getKey())) {
				threadIndex = i;
				break;
			}

			int curQueueSize = dispThreads[i].getQueueSize();
			if (curQueueSize < minQueueSize) {
				minQueueSize = curQueueSize;
				threadIndex = i;
			}
		}

		return dispThreads[threadIndex].enqueue(t);
	}


#ifdef DEBUG_THREAD_POOL
	int totalQueueSize() const
	{
		int size = 0;

		for (int i = 0; i < numberOfThreads; ++i) {
			size += dispThreads[i].getQueueSize();
		}

		return size;
	}
#endif


private:
	int numberOfThreads = 0;
	ThreadPoolThreadSpsc<Task> *dispThreads = nullptr;
};


#endif // THREAD_POOL_SPSC_H
