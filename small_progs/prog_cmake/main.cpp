#include <iostream>
#include <thread>

using namespace std;

void learn_time1();
long long int learn_thread_id();
std::thread::id learn_thread_id2();
int proxySplice();
int proxyCopy();
void learn_signals();
void learnStackProtector(int *buf, int size);
void stackProtector_getGuard(int *buf, int size);
void stackProtector_getGuard2(int *buf, int size);
    
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

    int buf[100];
    learnStackProtector(buf, 100);   
    for(int i=0;i<5;++i)
    {
       stackProtector_getGuard(buf,100);
       stackProtector_getGuard2(buf,100);
    }

    return 0;
}


