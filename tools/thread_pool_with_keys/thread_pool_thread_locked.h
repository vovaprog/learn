#ifndef THREAD_POOL_THREAD_LOCKED_H
#define THREAD_POOL_THREAD_LOCKED_H

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>


template<class Task>
class ThreadPoolThreadLocked
{
public:
    ThreadPoolThreadLocked(): inWorkFlags(nullptr)
	{
		runFlag.store(false);
		queueSize.store(0);
	}

    ThreadPoolThreadLocked(const ThreadPoolThreadLocked &tm) = delete;
    ThreadPoolThreadLocked(ThreadPoolThreadLocked &&tm) = delete;
    ThreadPoolThreadLocked& operator=(const ThreadPoolThreadLocked &tm) = delete;
    ThreadPoolThreadLocked& operator=(ThreadPoolThreadLocked &&tm) = delete;

    ~ThreadPoolThreadLocked()
	{
		{
			std::unique_lock<std::mutex> lock(mtx);
			runFlag.store(false);
		}

		cv.notify_one();
		th.join();

		if (inWorkFlags != nullptr)
			delete[] inWorkFlags;
	}


    int init(int numberOfKeys)
	{
		inWorkFlags = new std::atomic_int[numberOfKeys];
		for (int i = 0; i < numberOfKeys; ++i) {
			inWorkFlags[i].store(false);
		}

		runFlag.store(true);
        th = std::thread(&ThreadPoolThreadLocked<Task>::threadEntry, this);

		return 0;
	}


	bool inWork(int key)
	{
		return inWorkFlags[key].load() > 0;
	}


	int getQueueSize()
	{
		return queueSize.load();
	}


	int enqueue(Task t)
	{
		{
			std::unique_lock<std::mutex> lock(mtx);

			q.push(t);

			++inWorkFlags[t.getKey()];
			++queueSize;
		}

		cv.notify_one();

		return 0;
	}


protected:

	int threadEntry()
	{
		while (true) {
			{
				std::unique_lock<std::mutex> lock(mtx);
				while (queueSize.load() == 0 && runFlag.load()) {
					cv.wait(lock);
				}

				std::swap(q, qThread);

				if (runFlag.load() == false && qThread.size() == 0) {
					return 0;
				}
			}

			while (qThread.size() > 0) {
				Task t = qThread.front();
				qThread.pop();
				t.execute();
				--queueSize;
				--inWorkFlags[t.getKey()];
			}
		}
	}


protected:
	std::atomic_bool runFlag;
	std::atomic_int queueSize;
	std::atomic_int *inWorkFlags;	

	std::thread th;
	std::mutex mtx;
    std::condition_variable cv;

	std::queue<Task> q;
	std::queue<Task> qThread;
};


#endif // THREAD_POOL_THREAD_LOCKED_H

