#include <iostream>
#include <thread>

using namespace std;

void learn_time1();
long long int learn_thread_id();
std::thread::id learn_thread_id2();
int proxySplice();
int proxyCopy();
void learn_signals();
void learnStackProtector();
void learnSockets();   

int main()
{
	//learn_time1();

	//learn_thread_id();
	//learn_thread_id();

	//learn_thread_id2();
	//learn_thread_id2();

	//proxySplice();
	//proxyCopy();

	//learn_signals();

    //learnStackProtector();

    //cout << "sizeof(bool): " << sizeof(bool) << endl;

    learnSockets();

    return 0;
}


