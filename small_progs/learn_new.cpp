#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);


class User{
public:    
    int id, x;
    
    User()
    {
        cout <<"User ctr()\n";    
    }
    
    User(int id):id(id)
    {
        cout <<"User ctr int\n";
    }
    
    ~User()
    {
        cout <<"~User\n";    
    }
    
    void* operator new(size_t size)
    {
        cout <<"new operator size = "<<size<<"\n";
        return ::operator new(size);    
    }
    
    void operator delete(void *ptr)
    {
        cout <<"operator delete\n";
        ::operator delete(ptr);
    }

    void* operator new[](size_t size, double dArg, string sArg)
    {
        debug2("operator new[](%d %f %s)",(int)size,dArg,sArg.c_str());
        return ::operator new(size);    
    }
    
    void* operator new[](size_t size)
    {
        cout <<"new[] operator size = "<<size<<"\n";
        void* result = ::operator new[](size);
        uintptr_t intResult = (uintptr_t)result;
        cout <<"int pointer = "<<intResult<<endl;
        return result;
    }
    
    void operator delete[](void *ptr)
    {
        cout <<"operator delete[]\n";
        ::operator delete[](ptr);    
    }
};

class Client{
public:    
    int id, x;
    
    Client()
    {
        cout <<"Client ctr\n";
    }
    
    ~Client()
    {
        cout <<"~Client\n";
    }
};

void test1()
{
    for(int i=0;i<30;++i)
    {
        int *p = new (std::nothrow) int[100000000];
        //int *p = new int[100000000];
        
        if(p==nullptr)
        {
            printf("null\n");    
        }
        else
        {
            printf("NOT null\n");    
        }
    }    
}

void test2()
{
    //User *usr = new User(15);
    User *usrs = new User[5];

    uintptr_t intRet = (uintptr_t)usrs;
    cout <<"returned pointer = "<<intRet<<endl;    
    intRet-=4;
    int *retPointer = (int*)intRet;
    cout <<"prefix int: "<<*retPointer<<endl;
    
    delete []usrs;
    
    usrs = new (1.23,string("test")) User[5];
    
    delete []usrs;
}

//placement new
void test3()
{
    char *p = new char[1000000];
    
    Client *pCli1 = new (p) Client();
    pCli1->~Client();
    
    delete[] p;    
    
    //---------------------
    
    p=new char[sizeof(Client)*5];
    Client *pCli2 = reinterpret_cast<Client*>(p);
    
    for(int i=0;i<5;++i)
    {
        new (pCli2+i) Client();    
    }
    
    for(int i=4;i>=0;--i)
    {
        pCli2[i].~Client();    
    }
    
    delete[] p;
}

int main()
{
    //test1();
    //test2();
    test3();
    
    return 0;    
}

