#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);


int globalId=0;

class User{
public:
    User():id(globalId++)
    {
        cout <<"User "<<(int)id<<endl;
    }
    
    ~User()
    {
        cout <<"~User "<<(int)id<<endl;    
    }
    
    char id;
    int x;      
    char id2;
    
};

void test1()
{
    User usrs[5];    
    
    User *pUsrs = new User[5];
    delete[] pUsrs;
    
    User usr;
    
    cout <<"sizeof(User) = "<<sizeof(usr)<<endl;
    cout <<"sizeof(Users[5]) = "<<sizeof(usrs)<<endl;
    cout <<"sizeof(User*) = "<<sizeof(pUsrs)<<endl;    
}

//==============================================================================

#define print(arg) cout<<#arg<<" = "<<arg<<endl;

class DataChar{
public:    
    char c;
};

class DataIntChar{
public:
    int i;
    char c;    
};

class DataCharInt{
public:    
    char c;
    int i;
};

class DataCharIntChar{
public:
    char c1;
    int i;
    char c2;    
};

void test2()
{
    print(sizeof(DataChar));
    print(sizeof(DataIntChar));
    print(sizeof(DataCharInt));
    print(sizeof(DataCharIntChar));
}

//==============================================================================


int main()
{
    test2();
    
    return 0;    
}
