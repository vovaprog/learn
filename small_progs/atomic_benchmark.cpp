#include <bits/stdc++.h>

#include "../SimpleProfiler.h"

using namespace std;
/*
home core2quad q9550:
ints: 153
atomics: 1063
ints cas: 149
atomics cas: 1509
atomics cas relaxed: 1507
atomics fetch_add: 1060
atomics fetch_add relaxed: 1060
*/

const int BSIZE = 100000000;

int ibuf[BSIZE];
atomic_int abuf[BSIZE];


int main()
{
    for(int i=0;i<BSIZE;++i) ibuf[i]=0;
    for(int i=0;i<BSIZE;++i) abuf[i].store(0);
    
    {
        SimpleProfiler prof("ints");
        
        for(int i=0;i<BSIZE;++i)
        {
            ++ibuf[i];
        }
    }
    
    {
        SimpleProfiler prof("atomics");
        
        for(int i=0;i<BSIZE;++i)
        {
            ++abuf[i];
        }
    }

    {
        SimpleProfiler prof("ints cas");
        
        for(int i=0;i<BSIZE-2;++i)
        {
            if(ibuf[i]==ibuf[i+1])
                ibuf[i]=ibuf[i+2];
        }
    }

    {
        SimpleProfiler prof("atomics cas");
        
        int a=5,b=6;
        
        for(int i=0;i<BSIZE;++i)
        {
            abuf[i].compare_exchange_strong(a, b);
        }
    }

    {
        SimpleProfiler prof("atomics cas relaxed");
        
        int a=5,b=6;
        
        for(int i=0;i<BSIZE;++i)
        {
            abuf[i].compare_exchange_weak(a, b, std::memory_order_relaxed, std::memory_order_relaxed);
        }
    }

    {
        SimpleProfiler prof("atomics fetch_add");
        
        int a=5,b=6;
        
        for(int i=0;i<BSIZE;++i)
        {
            abuf[i].fetch_add(5);
        }
    }

    {
        SimpleProfiler prof("atomics fetch_add relaxed");
        
        int a=5,b=6;
        
        for(int i=0;i<BSIZE;++i)
        {
            abuf[i].fetch_add(5, std::memory_order_relaxed);
        }
    }
    
    return 0;
}


