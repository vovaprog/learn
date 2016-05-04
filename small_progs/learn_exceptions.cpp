#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);

class MyExceptionA{
public:
    MyExceptionA(char *msg):msg(msg){}
    
    virtual 
    string getMessage()
    {
        return msg;    
    }
protected:    
    string msg;
};

class MyExceptionB : public MyExceptionA{
public:
    MyExceptionB(char *msg):MyExceptionA(msg)
    {
    
    }
    
    virtual 
    string getMessage()
    {
        return "B("+MyExceptionA::getMessage()+")";
    }
};

void test_exceptions1()
{
    try{
        throw MyExceptionB("a1");
    }catch(MyExceptionA ex){
        cout <<"catch MyExceptionA: "<< ex.getMessage()<<endl;                
    }catch(MyExceptionB &ex){
        cout <<"catch MyExceptionB: "<< ex.getMessage()<<endl;    
    }catch(...){
        cout <<"catch ...\n";
    }
}

void test_exceptions2()
{
    try{
        throw 1.33f;
    }catch(char c){
        cout <<"catch char"<<endl;
    }catch(double d){
        cout <<"catch double"<<endl;
    }catch(long long ll){
        cout <<"catch long long"<<endl;
    }catch(long l){
        cout <<"catch long"<<endl;           
    }catch(int i){
        cout <<"catch int"<<endl;
    }
}

int main()
{
    test_exceptions1();
    test_exceptions2();
    
    return 0;    
}

