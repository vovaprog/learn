#include <bits/stdc++.h>

using namespace std;

class Base;

Base *p1 = nullptr;
Base *p2 = nullptr;

class Base{
public:
    
    virtual void fun1()
    {
        p1 = this;
    }
    
    virtual void print()
    {
        cout <<"base"<<endl;
    }
};


class Child: public Base{
public:
    
    void fun1() override
    {
        p2 = this;
        Base::fun1();
    }
    
    void print() override
    {
        cout <<"child"<<endl;
    }    
};


int main()
{
    Child ch;
    ch.fun1();
    
    p1->print();
    p2->print();
    
    return 0;
}
