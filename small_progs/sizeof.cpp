#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);

//=====================================================================
#define debug3(args...) { vector<string> v = splitArgNames(#args); debugPrint(v.begin(), args); }
vector<string> splitArgNames(const string& s) 
{ vector<string> v; stringstream ss(s); for (string x; getline(ss, x, ',');) { v.emplace_back(x); } return move(v); }
void debugPrint(vector<string>::iterator it) { cout <<"\n"; }
template<typename T, typename... Args>
void debugPrint(vector<string>::iterator it, T head, Args... args) 
{ cout << *it <<" = "<< head << "     "; debugPrint(++it, args...); }
//=====================================================================

typedef long long int int64;

class A{
public:    
    A(){cout <<"ctr\n";}
    ~A(){cout <<"dest\n";}
    const long long int MAX_VALUE=123;
};

A func()
{
    return A();
}

struct B{    
    char a[20];
    char b[16];
    long long int x;
};

int main()
{
    cout <<sizeof func() <<endl;        
    
    char buf[4];
    
    cout <<sizeof(buf)<<endl;
    
    A arr[4];
    
    cout <<sizeof(arr)<<endl;

    
    cout <<sizeof(B) <<endl;
    
    return 0;
}


