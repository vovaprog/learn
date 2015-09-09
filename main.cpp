#include <iostream>
#include <memory>
#include <string.h>

#include "body.h"
#include "model.h"

#include "learn_signals.h"
#include "learn_system.h"
#include "wget.h"
#include "smart_pointers.h"
#include "http_server.h"
#include "shared_memory.h"
#include "constructor_exception.h"
#include "systemv_semaphores.h"
#include "learn1.h"

using namespace std;

void printBody(Body *pb)
{
	cout <<pb->toString()<<endl;
}

void learn1()
{
	Model m;
	m.init();

	for(auto const& pBody : m.bodies)
	{
		cout << pBody.get()->toString()<<endl;
	}

	cout <<"before clear"<<endl;
	m.bodies.clear();
	cout <<"after clear"<<endl;

	//printBody(m.bodies[0].get());
}

void learn2()
{
	cout <<"0"<<endl;
	unique_ptr<Body> pBody;

	if(pBody)
	{
		cout <<"true"<<endl;
	}
	else
	{
		cout <<"false"<<endl;	
	}

	cout <<"a"<<endl;
	pBody=unique_ptr<Body>(new Spaceship("mars1"));
	cout <<"b"<<endl;
	pBody=unique_ptr<Body>(new Spaceship("venera2"));
	cout <<"c"<<endl;
}

void learn3()
{
	Model m;
	m.init();

	cout <<"<<<<<<<<<<<<<"<<endl;

	m.bodies[3]=unique_ptr<Body>(new Spaceship("juno"));

	cout <<">>>>>>>>>>>>>"<<endl;
}

int main()
{
	try{
		cout <<"main enter"<<endl;

		//learn3();
		//learn_signals();
		//learn_system();
		//wget();
		//test_smart_pointers();
		//http_server();
		//http_server_select();
		//http_server_poll();
		//sharedMemoryCreate();
		//sharedMemoryWrite();
		//sharedMemoryRead();
		//testConstructorException();
		//learnProcessSemaphores();
		//learnPosixSemaphores();
		//learnMemoryMap();
        //learnPosixSharedMemory();
        //learnMessageQueue();
        learnPriorityQueue();

		cout <<"main exit"<<endl;
		return 0;
	}catch(string s){
		fflush(stdout);
		throw;
		//cout << "unhandled exception: "<<s<<endl;
		//return -1;
	}
}

