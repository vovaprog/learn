#ifndef THREAD_POOL_LOCKED_H
#define THREAD_POOL_LOCKED_H

#include <vector>
#include <climits>
#include <errno.h>

#include "thread_pool_thread_locked.h"


template<class Task>
class ThreadPoolLocked
{
public:
    ThreadPoolLocked() = default;

    ThreadPoolLocked(const ThreadPoolLocked &tm) = delete;
    ThreadPoolLocked(ThreadPoolLocked &&tm) = delete;
    ThreadPoolLocked& operator=(const ThreadPoolLocked &tm) = delete;
    ThreadPoolLocked& operator=(ThreadPoolLocked &&tm) = delete;


    ~ThreadPoolLocked()
	{
		if (dispThreads != nullptr) {
			delete[] dispThreads;
		}
	}


    int init(int numberOfThreads, int numberOfKeys, int maxQueueSize)
	{
		this->numberOfThreads = numberOfThreads;
        this->maxQueueSize = maxQueueSize;
        dispThreads = new ThreadPoolThreadLocked<Task>[numberOfThreads];

		for (int i = 0; i < numberOfThreads; ++i) {
            dispThreads[i].init(numberOfKeys);
		}

		return 0;
	}


	int enqueue(Task t)
	{
        int threadQueueSize = INT_MAX;
        int threadIndex = 0;

        for (int i = 0; i < numberOfThreads; ++i) {

            if (dispThreads[i].inWork(t.getKey())) {
                threadQueueSize = dispThreads[i].getQueueSize();
                threadIndex = i;
                break;
			}

            int curQueueSize = dispThreads[i].getQueueSize();
            if (curQueueSize < threadQueueSize) {
                threadQueueSize = curQueueSize;
                threadIndex = i;
			}
		}

        if(maxQueueSize > 0 && threadQueueSize > maxQueueSize)
            return EAGAIN;

        return dispThreads[threadIndex].enqueue(t);
	}


#ifdef DEBUG_THREAD_POOL
    int totalQueueSize()
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
    int maxQueueSize = 0;
    ThreadPoolThreadLocked<Task> *dispThreads = nullptr;
};


#endif // THREAD_POOL_LOCKED_H
