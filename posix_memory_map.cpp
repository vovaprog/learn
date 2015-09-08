#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void* openPosixSharedMemory()
{
    int shm_fd = shm_open("/MyMemoryMap",O_CREAT | O_RDWR, /*S_IRWXU | S_IRWXG*/0777);
        
    if(shm_fd==-1)
    {        
        perror("shm_open");
        return NULL;
    }
        
    if ( ftruncate(shm_fd, 1000) == -1 ) {
        perror("ftruncate");
        return NULL;
    }    
    
    void *memory = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (memory == NULL) {
        perror("mmap");
        return NULL;
    }
    
    return memory;
}

void learnPosixSharedMemory()
{
    void *memory=openPosixSharedMemory();
    
    if(memory!=NULL)
    {        
//        strcpy((char*)memory,"hello, world!");
        
        printf("%s\n",(char*)memory);
    }
}
