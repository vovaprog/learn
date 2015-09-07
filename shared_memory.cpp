#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int getExecutableName(char *name,int nameSize)
{
   int resultSize = readlink("/proc/self/exe",name,nameSize-1);
    
    if(resultSize==-1)
    {
        return -1;       
    }
    
    name[resultSize]=0;
    
    return 0;     
}


void* sharedMemoryCreate()
{
    const int maxExeFileName=1000;
    char exeFileName[maxExeFileName];  
    
    if(getExecutableName(exeFileName,maxExeFileName)!=0)
    {
        printf("getExecutableName failed\n");
        return NULL;
    }
        
    printf("exe: <%s>\n",exeFileName);
    
    key_t ipc_key = ftok(exeFileName,33);
    
    if(ipc_key==-1)
    {
        printf("ftok failed\n");
        return NULL;
    }
    
    int shm_id = shmget(ipc_key,1000,IPC_CREAT | 0660);
    
    if(shm_id<0)
    {
        printf("shmget failed: %s\r\n",strerror(errno));
        return NULL;
    }
    
    void *memory=shmat(shm_id,0,0);
    
    if((int)memory==-1)
    {
        printf("shmat failed: %s\r\n",strerror(errno));
        return NULL;    
    }
    
    return memory;
}

void sharedMemoryWrite()
{
    char *memory = (char*)sharedMemoryCreate();
    
    sprintf(memory,"hello, world!");
    
}

void sharedMemoryRead()
{
    char buf[1000];
    
    char *memory = (char*)sharedMemoryCreate();
    
    memcpy(buf,memory,1000);
    buf[999]=0;
    
    printf("read: <%s>\n",buf);
}