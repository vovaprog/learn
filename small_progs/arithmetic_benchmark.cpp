#include <bits/stdc++.h>

#include "../SimpleProfiler.h"

using namespace std;


const int BSIZE = 10000;
const int ITERS = 100000;

/*
Another way to select templates - return value.

template<typename T>
typename std::enable_if<!std::is_integral<T>::value>::type test_for_ints(T x[BSIZE],T y[BSIZE],T z[BSIZE]) 
{
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type test_for_ints(T x[BSIZE],T y[BSIZE],T z[BSIZE])
{
}
*/

template<class T , typename std::enable_if<!std::is_integral<T>::value>::type* = nullptr >
void test_for_ints(T *x,T *y,T *z)
{    
}


template<class T , typename std::enable_if<std::is_integral<T>::value>::type* = nullptr >
void test_for_ints(T *x,T *y,T *z)
{
    {
        SimpleProfiler prof("|");
        
        for(int k = 0;k<ITERS;++k)
        {
            for(int i=0;i<BSIZE;++i)
            {
                z[i] = (x[i] | y[i]);
            }        
        }
    }
    
    {
        SimpleProfiler prof("&");
        
        for(int k = 0;k<ITERS;++k)
        {
            for(int i=0;i<BSIZE;++i)
            {
                z[i] = (x[i] & y[i]);
            }        
        }
    }
}


template<class T>
int test(const char *typeName)
{
    cout <<"=== "<<typeName<<" ==="<<endl;
    
    T x[BSIZE], y[BSIZE], z[BSIZE];    
    
    for(int i=0;i<BSIZE;++i)
    {
        x[i] = i;
        y[i] = i;
        z[i] = i;
    }
    
    {
        SimpleProfiler prof("add");
        
        for(int k = 0;k<ITERS;++k)
        {
            for(int i=0;i<BSIZE;++i)
            {
                z[i] = x[i] + y[i];
            }        
        }
    }
    
    {
        SimpleProfiler prof("mul");
        
        for(int k = 0;k<ITERS;++k)
        {
            for(int i=0;i<BSIZE;++i)
            {
                z[i] = x[i] * y[i];
            }        
        }
    }

    for(int i=0;i<BSIZE;++i)
    {
        if(y[i] == 0) y[i]=1;
    }    
    
    {
        SimpleProfiler prof("div");
        
        for(int k = 0;k<ITERS;++k)
        {
            for(int i=0;i<BSIZE;++i)
            {
                z[i] = x[i] / y[i];
            }        
        }
    }
   
    test_for_ints<T>(x, y, z);
    

    if(x[100]) return 1;
    if(y[100]) return 1;
    if(z[100]) return 1;
    
    return 0;
}

int main()
{
    test<char>("char");
    test<short int>("short int");
    test<int>("int");
    test<long long int>("long long int");
    test<float>("float");
    test<double>("double");
    test<long double>("long double");
    
    return 0;
}
