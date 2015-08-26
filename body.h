#pragma once

#include <string>
#include <iostream>

using namespace std;

class Body{
protected:
	double weight;
	string name;
public:
	Body()
	{
		cout <<"Body +constructor"<<endl;
		weight=33.0;
		name="earth";
	}

	Body(const string &s):name(s)
	{
		cout <<"Body +constructor   "<<name<<endl;
		weight=33.0;
	}

	Body(const Body& b)
	{
		cout <<"Body copy +constructor"<<endl;
		weight=b.weight;
		name=b.name;
	}

	virtual ~Body()
	{
		cout <<"Body -destructor   "<<name<<endl;
	}

	Body& operator=(const Body &b)
	{
		cout <<"Body operator ="<<endl;
		weight=b.weight;
		name=b.name;
		return *this;
	}

	virtual string toString()
	{
		return "body "+name+" "+to_string(weight);
	}

};

