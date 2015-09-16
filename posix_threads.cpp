#include <pthread.h> 
#include <iostream>
#include <unistd.h>

using namespace std;

struct MyThreadParameters
{
    char printSymbol;
    int x;    
};

struct MyThreadResult
{
    char resultChar;
};

int thread_flag=0;  
pthread_cond_t thread_flag_cv;  
pthread_mutex_t thread_flag_mutex;  

static pthread_key_t thread_key;

void cleanup_function2 (void* p)  
{ 
    cout <<" [[ cleanup 2 ]] ";     
}  

void *threadEntry(void *threadParams)
{
    MyThreadParameters* params =(MyThreadParameters*)threadParams;
    
    int old_cancel_state;
    
    if(params->printSymbol!='x')
    {
        pthread_setspecific(thread_key, (void*)pthread_self());         
    }
    
    pthread_cleanup_push(cleanup_function2, NULL);
    
    //pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &old_cancel_state); //thread can't be cancelled here
    for(int i=0;i<1000;i++)
    {
        cout <<params->printSymbol;
    }
    //pthread_setcancelstate (old_cancel_state, NULL); 

    MyThreadResult *res=new MyThreadResult();
    res->resultChar=params->printSymbol+10;    
    
    delete params;
    
    
    
             
    
    
    cout <<"waiting exit flag"<<endl;
    
    pthread_mutex_lock (&thread_flag_mutex);  
    while (thread_flag==0)
    {
        cout <<"!#!#"<<endl;
        pthread_cond_wait (&thread_flag_cv, &thread_flag_mutex);
    }
    pthread_mutex_unlock (&thread_flag_mutex);
    
    cout <<"exiting thread"<<endl<<flush;
    
    return res;
    
    pthread_cleanup_pop(1);
}

void cleanup_function (void*  p)  
{ 
   cout <<"cleanup function"<<(long long int)p<<endl;  
}  

void set_cv(int cv_value)
{
    pthread_mutex_lock (&thread_flag_mutex);  
    
    thread_flag  =  cv_value;  
    
    //pthread_cond_signal  (&thread_flag_cv);
    pthread_cond_broadcast  (&thread_flag_cv);
    
    pthread_mutex_unlock  (&thread_flag_mutex);  
}      

void init_cv ()  
{   
   pthread_mutex_init (&thread_flag_mutex, NULL);  
   pthread_cond_init (&thread_flag_cv, NULL);  
    
   thread_flag = 0;  
}  


void learnPosixThreads()
{
    pthread_t threads[5]; 
    
    pthread_key_create (&thread_key, cleanup_function);
    
    
    init_cv();
    
    
    pthread_mutex_t mutex;    
    pthread_mutex_init (&mutex,  NULL);  
    
    pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
    
    pthread_mutex_lock(&mutex2);
    pthread_mutex_unlock(&mutex2); 
    
    int i;    
    for (i = 0; i < 5; ++i)
    {
        //pthread_attr_t attr; 
        //pthread_attr_init (&attr); 
        //pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED); 
        
        MyThreadParameters *params=new MyThreadParameters();
        params->printSymbol='a'+i;
        
        pthread_create (&(threads[i]), /*&attr*/ NULL, threadEntry, params);
    }
    
    //pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL); 
    
    sleep(5);
    
    set_cv(1);    
    
    for (i = 0; i < 5; ++i)  
    {
        MyThreadResult *result;
        pthread_join (threads[i], (void**)&result);
        cout <<" "<<result->resultChar;
    }
    cout <<endl;
        
    //pthread_exit(NULL);
}

