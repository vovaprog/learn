#ifndef THREAD_POOL_THREAD_SPSC_H
#define THREAD_POOL_THREAD_SPSC_H

#include <thread>
#include <atomic>
#include <boost/lockfree/spsc_queue.hpp>


template<class Task>
class ThreadPoolThreadSpsc
{
public:
	ThreadPoolThreadSpsc(): inWorkFlags(nullptr), q(nullptr)
	{
		runFlag.store(false);
		queueSize.store(0);
	}

	ThreadPoolThreadSpsc(const ThreadPoolThreadSpsc &tm) = delete;
	ThreadPoolThreadSpsc(ThreadPoolThreadSpsc &&tm) = delete;
	ThreadPoolThreadSpsc& operator=(const ThreadPoolThreadSpsc &tm) = delete;
	ThreadPoolThreadSpsc& operator=(ThreadPoolThreadSpsc &&tm) = delete;


	~ThreadPoolThreadSpsc()
	{
		runFlag.store(false);
		th.join();

		if (inWorkFlags != nullptr)
			delete[] inWorkFlags;

		if (q != nullptr)
			delete q;
	}


	int init(int numberOfKeys, int maxQueueSize)
	{
		inWorkFlags = new std::atomic_int[numberOfKeys];
		for (int i = 0; i < numberOfKeys; ++i) {
			inWorkFlags[i].store(0);
		}

		q = new boost::lockfree::spsc_queue<Task>(maxQueueSize);		

		runFlag.store(true);
		th = std::thread(&ThreadPoolThreadSpsc<Task>::threadEntry, this);

		return 0;
	}


	bool inWork(int key) const
	{
		return inWorkFlags[key].load() > 0;
	}


	int getQueueSize() const
	{
		return queueSize.load();
	}


	int enqueue(Task t)
	{
		if (q->push(t)) {
			++inWorkFlags[t.getKey()];
			++queueSize;

			return 0;
		} else {
			return EAGAIN;
		}
	}


protected:

	int processQueue()
	{
		Task t;
		int processedCount = 0;

		while (q->pop(t)) {
			t.execute();
			--queueSize;
			--inWorkFlags[t.getKey()];
			++processedCount;
		}
		return processedCount;
	}

	void threadEntry()
	{
		while (runFlag.load()) {

			if (processQueue() == 0) {
				std::this_thread::yield();
			}
		}

		processQueue();
	}


protected:
	std::atomic_bool runFlag;
	std::atomic_int queueSize;
	std::atomic_int *inWorkFlags;

	std::thread th;

	boost::lockfree::spsc_queue<Task> *q;
};


#endif // THREAD_POOL_THREAD_SPSC_H

