#include <iostream>
#include <algorithm>
#include <string.h>

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


class MyArray{
public:
    MyArray(int size):size(size),p(new int[size])
    {
        cout <<"MyArray ctr"<<endl;
    }

    MyArray(const MyArray &ar):
        size(ar.size),p(new int[ar.size])
    {
        cout <<"MyArray copy ctr"<<endl;
        
        memcpy(p,ar.p,sizeof(int) * size);            
    }
    
    MyArray(MyArray &&ar):
        size(ar.size),p(ar.p)
    {
        cout <<"MyArray move ctr"<<endl;
        ar.size=0;
        ar.p=nullptr;
    }
    
    ~MyArray()
    {
        cout <<"MyArray ~~~"<<endl;
        
        delete[] p;
    }
    
    MyArray& getThis()
    {
        cout <<"MyArray getThis"<<endl;
        return *this;    
    }
    
    MyArray getOther()
    {
        cout <<"MyArray getOther"<<endl;
        
        return MyArray(*this);    
    }
    
    void swap(MyArray &ar)
    {
        std::swap(size,ar.size);
        std::swap(p,ar.p);
    }
    
    MyArray& operator=(MyArray ar)
    {
        cout <<"MyArray assign operator"<<endl;
        swap(ar);
        return *this;
    }
    
    int getSize() { return size; }
    
private:    
    int size;
    int* p;
};

void learn_classes1()
{
    //Base b;
    //Child1 b;
    //b.print1();
    
    MyArray ar1(30), ar2(50);
    
    //ar1 = MyArray(100).getOther();
    MyArray ar3(ar1.getOther());
    
    cout <<"ar1 size: "<<ar1.getSize()<<endl;
    cout <<"ar2 size: "<<ar2.getSize()<<endl;
}
