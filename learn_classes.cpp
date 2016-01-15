#include <iostream>

using namespace std;

class Base{
public:
    Base()
    {
        cout <<"Base ctr"<<endl;
    }
    
    void print1()
    {
        cout <<"Base print"<<endl;
    }
    
protected:
    ~Base()
    {
        cout <<"Base ~~~"<<endl;
    }
};

class Child1:public Base{    
public:    
    void print1()
    {
        cout <<"Child1 print"<<endl;
    }
};

void learn_classes1()
{
    //Base b;
    Child1 b;
    b.print1();
}
