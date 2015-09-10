#include <stdio.h>
#include <string.h>
#include <cstdint>

extern char _binary_resource_file_txt_start[];
extern char _binary_resource_file_txt_end[];
extern int _binary_resource_file_txt_size;

void learnResources()
{
    for (char* p = _binary_resource_file_txt_start; p != _binary_resource_file_txt_end; ++p) 
    {
        putchar( *p);
    }  
    
    intptr_t resourceSizeP = (intptr_t)(&_binary_resource_file_txt_size);
    int resourceSize=(int)resourceSizeP;
    
    printf("size: %d\n", resourceSize);

    

    char buf[1000];
    strncpy(buf,  _binary_resource_file_txt_start,resourceSize);
    buf[resourceSize]=0;
    printf("<%s>\n",buf);
    
}
