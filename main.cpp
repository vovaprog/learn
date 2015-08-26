#include <iostream>
#include <memory>

#include "body.h"
#include "model.h"

#include "learn_signals.h"

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
	cout <<"main enter"<<endl;

	//learn3();
	learn_signals();

	cout <<"main exit"<<endl;
	return 0;
}

