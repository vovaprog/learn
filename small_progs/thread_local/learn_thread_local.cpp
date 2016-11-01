#include <bits/stdc++.h>

#include <unistd.h>
#include <sys/time.h>

using namespace std;

int result = 0;

int tLocal(int x);
int simple(int x);
int thread_local_accum(int x);

void threadEntryTLocal()
{
    thread_local_accum(5);
    
    for(int i=0;i<3;++i)
    {
        result += tLocal(i);    
    }      
}

void threadEntrySimple()
{
    for(int i=0;i<3;++i)
    {
        result += simple(i);    
    }      
}


long long int getMilliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (long long int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));		
}


int main()
{
    const int threadCount = 4;
    thread *threads[threadCount];
    
    {
        long long int millisStart = getMilliseconds();
        
        for(int i=0; i<threadCount ;++i)
        {
            threads[i] = new thread(threadEntryTLocal);
        }    
            
        for(int i=0; i<threadCount ;++i)
        {
            threads[i]->join();
            delete threads[i];
            threads[i] = nullptr;
        }
        
        long long int diff = getMilliseconds() - millisStart;
    
        cout << "millis thread local: " << diff <<endl;
    }
    
    {
        long long int millisStart = getMilliseconds();
        
        for(int i=0; i<threadCount ;++i)
        {
            threads[i] = new thread(threadEntrySimple);
        }    
            
        for(int i=0; i<threadCount ;++i)
        {
            threads[i]->join();
            delete threads[i];
            threads[i] = nullptr;
        }
        
        long long int diff = getMilliseconds() - millisStart;
    
        cout << "millis simple: " << diff <<endl;
    }
    
    
    cout << "result: "<< result<<endl;
    
    return 0;    
}
