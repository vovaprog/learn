#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>

void learnPosixSemaphores()
{
    sem_t *mutex = sem_open("MySemaphoreName",O_CREAT,0660,1);
    
    if(mutex==SEM_FAILED)
    {
        printf("sem_open failed\n");
        return;
    }
    
    if(sem_wait(mutex)!=0)
    {
        printf("sem_wait failed\n");
        return;
    }
    
    printf("under mutex\n");
    
    if(sem_post(mutex)!=0)
    {
        printf("sem_post failed\n");
        return;        
    }
    
    if(sem_post(mutex)!=0)
    {
        printf("sem_post failed\n");
        return;        
    }

    int val;
    if(sem_getvalue(mutex,&val)!=0)
    {
        printf("sem_getvalue failed\n");
        return;
    }
    printf("value: %d\n",val);
        
    if(sem_close(mutex)!=0)
    {
        printf("sem_close failed\n");
        return;
    }
    
    if(sem_unlink("MySemaphoreName")!=0)
    {
        printf("sem_unlink failed\n");
        return;
    }    
}

