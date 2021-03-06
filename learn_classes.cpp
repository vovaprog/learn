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


class TestDest{
public:
    TestDest():counterLocal(++counterGlobal)
    {
        cout <<"TestDest ctr "<<counterLocal<<endl;
    }
    ~TestDest()
    {
        cout <<"TestDest ~~~ "<<counterLocal<<endl;        
    }
public:    
    int counterLocal;
    static int counterGlobal;
};

int TestDest::counterGlobal = 0;


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

class MyString {
public:
    MyString() 
    {
        cout <<"MyString ctr()"<<endl;
        
        p = new char[1];
        p[0] = 0;
    }
    
    MyString(const char *c)
    {
        cout <<"MyString ctr(char*)"<<endl;
        
        p = new char[strlen(c)+1];
        strcpy(p, c);
    }
    
    MyString(const MyString &s)
    {
        cout <<"MyString copy ctr"<<endl;
        
        p = new char[s.length()+1];
        strcpy(p, s.p);
    }
    
    MyString(MyString &&s)
    {
        cout <<"MyString move ctr"<<endl;
        
        p = s.p;
        s.p = nullptr;
    }
    
    ~MyString()
    {
        cout <<"MyString ~~~"<<endl;
        
        delete[] p;
    }
    
    int length() const
    {
        return strlen(p);
    }
    
    MyString& operator=(MyString s)
    {
        cout <<"MyString operator="<<endl;
        
        swap(s);
        return *this;
    }
    
    MyString operator+(const MyString &s) const
    {
        cout <<"MyString operator+"<<endl;
        
        char *newP = new char[length() + s.length() + 1];
        strcpy(newP, p);
        strcat(newP, s.p);
        return MyString(newP);
    }
    
    char* c_str()
    {
        return p;
    }
    
protected:    
    void swap(MyString &s)
    {
        std::swap(p, s.p);
    }
    
    char *p = nullptr;
};

void learn_classes1()
{
    //Base b;
    //Child1 b;
    //b.print1();
    

    TestDest *p=new TestDest[5];
    delete[] p;    

    /*MyArray ar1(30), ar2(50);
    
    //ar1 = MyArray(100).getOther();
    MyArray ar3(ar1.getOther());
    
    cout <<"ar1 size: "<<ar1.getSize()<<endl;
    cout <<"ar2 size: "<<ar2.getSize()<<endl;*/
    
    MyString s1("hello"), s2("world");
    //MyString s3(s1 + s2);
    s1 = std::move(s1 + s2);
    cout <<s1.c_str()<<endl;

}
