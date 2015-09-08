#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

void learnMemoryMap()
{
    int fd = open("./wget.c",O_RDWR);
    struct stat sb;
    
    if(fd==-1)
    {
        perror ("open");
        return;
    }
    
    if (fstat (fd, &sb) == -1) 
    {
        perror ("fstat");
        return;
    }

    if (!S_ISREG (sb.st_mode)) 
    {
        fprintf (stderr, "is not a file\n");
        return;
    }        
    
    void * file_memory = mmap(0, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    
    ((char*)file_memory)[sb.st_size - 1]=0;
    
    printf("<%s>\n",(char*)file_memory);
    
    munmap(file_memory,1000);    
}


