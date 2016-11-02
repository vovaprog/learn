#include <iostream>
#include <thread>

using namespace std;

void learn_time1();
long long int learn_thread_id();
std::thread::id learn_thread_id2();

int main()
{
	learn_time1();

	learn_thread_id();
	//learn_thread_id();

	//learn_thread_id2();
	//learn_thread_id2();

    return 0;
}
