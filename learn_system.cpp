#include "learn_system.h"

#include <iostream>
#include <unistd.h>

using namespace std;

void learn_system1()
{
    pid_t result=fork();
    
    if(result==0)
    {
        //for(int i=0;i<100000;i++)
        {
            cout <<"c";
        }
    }
    else if(result>0)
    {
        /*for(int i=0;i<100000;i++)
        {        
            cout <<"p";
        }*/
                 
        int result = execlp("echo","echo","hello!","world!",NULL);
        cout <<"exec failed! "<<result<<endl;
    }
    else
    {
        cout <<"error!"<<endl;    
    }
}


void learn_system()
{
    learn_system1();
}
