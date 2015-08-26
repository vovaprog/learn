#pragma once

#include <string>
#include <iostream>

#include "body.h"

using namespace std;

class Spaceship : public Body{
public:
	Spaceship(const string &name):Body(name)	
	{
		cout <<"Spaceship +constructor "<<name<<endl;
		weight=33.0;
	}

	Spaceship(const Spaceship& b)
	{
		cout <<"Spaceship copy +constructor"<<endl;
		weight=b.weight;
		name=b.name;
	}

	virtual ~Spaceship()
	{
		cout <<"Spaceship -destructor   "<<name<<endl;
	}

	Spaceship& operator=(const Spaceship &b)
	{
		cout <<"Spaceship operator ="<<endl;
		weight=b.weight;
		name=b.name;
		return *this;
	}

	virtual string toString()
	{
		return "Spaceship "+name+" "+to_string(weight);
	}
};
