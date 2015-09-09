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

    bool operator<(const Body &b) const
    {
        return this->name > b.name;
    }

	virtual string toString()
	{
		return "body "+name+" "+to_string(weight);
	}
    
    operator std::string()
    {
        return name;
    }
    
template<typename charT, typename traits>    
friend std::basic_ostream<charT,traits> &
operator<< (std::basic_ostream<charT,traits> &lhs, Body &rhs) {
    return lhs << rhs.toString();
} 

};

