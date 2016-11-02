#include <pthread.h>
#include <iostream>
#include <thread>

using namespace std;

long long int learn_thread_id()
{
	pthread_t tid = pthread_self();

	return (long long int)tid;
}

std::thread::id learn_thread_id2()
{
	std::thread::id tid = std::this_thread::get_id();

	return tid;
}

