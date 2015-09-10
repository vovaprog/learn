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

	Spaceship(const string &name,double weight):Body(name)	
	{
        this->weight=weight;        
		cout <<"Spaceship +constructor "<<name<<endl;		
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

	virtual string toString() const
	{
		return "Spaceship "+name+" "+to_string(weight);
	}
    
    template<typename charT, typename traits>    
    friend std::basic_ostream<charT,traits> &
    operator<< (std::basic_ostream<charT,traits> &lhs, const Spaceship &rhs) {
        return lhs << rhs.toString();
    }
};
