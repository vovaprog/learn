#include <string>
#include <iostream>

using namespace std;

/*
The order of member initializers in the list is irrelevant: the actual order of initialization is as follows:
1) If the constructor is for the most-derived class, virtual base classes are initialized in the order in which they appear in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists)
2) Then, direct base classes are initialized in left-to-right order as they appear in this class's base-specifier list
3) Then, non-static data members are initialized in order of declaration in the class definition.
4) Finally, the body of the constructor is executed
*/

class Child1
{
public:
	Child1()
	{
		cout <<"child1 ctr"<<endl;
	}
	
	~Child1()
	{
		cout <<"child1 dest"<<endl;
	}	
	
	string toString()
	{
		return string("child1");
	}	
};

class Child2
{
public:
	Child2()
	{
		cout <<"child2 ctr"<<endl;		
	}
	
	~Child2()
	{
		cout <<"child2 dest"<<endl;
	}	
	
	string toString()
	{
		return string("child2");
	}
};

class Child3
{
public:
	Child3()
	{
		cout <<"child3 ctr"<<endl;
		//throw string("child3 exception");
	}
	
	~Child3()
	{
		cout <<"child3 dest"<<endl;
	}	
	
	string toString()
	{
		return string("child3");
	}
};

class Parent
{
public:
		Parent() try:c1(),c2(),c3()
		{
			cout <<"parent ctr"<<endl;
			throw string("constructor test exception");
		}
		catch(string)
		{
			cout <<"parent catch"<<endl;
			throw;
		}

		string toString()
		{
			return c1.toString()+c2.toString()+c3.toString();
		}

private:
		Child1 c1;
		Child2 c2;	
		Child3 c3;
};

void testConstructorException()
{
	Parent p;
	
}

