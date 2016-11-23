#include <stdio.h>

void _learnStackProtector(int *buf, int size)
{
    for(int i = 0;i<size;++i)
    {
        buf[i] = i;
    }

    return;
}


void stackProtector_getGuard(int *buf, int size)
{
    for(int i = 0;i<size;++i)
    {
        buf[i] = i;
    }

    unsigned long long int guard = 0;

    asm(".intel_syntax noprefix;"
        "mov    %0,QWORD PTR fs:40;" 
        ".att_syntax;" :
        "=r" (guard));

    printf("guard1: %llx\n",guard);
        
    return;
}

void stackProtector_getGuard2(int *buf, int size)
{
    for(int i = 0;i<size;++i)
    {
        buf[i] = i;
    }

    unsigned long long int guard = 0;

    asm(".intel_syntax noprefix;"
        "mov    %0,QWORD PTR fs:40;" 
        ".att_syntax;" :
        "=r" (guard));

    printf("guard2: %llx\n",guard);
        
    return;
}

void learnStackProtector()
{
    int buf[100];
    _learnStackProtector(buf, 100);   
    for(int i=0;i<5;++i)
    {
       stackProtector_getGuard(buf,100);
       stackProtector_getGuard2(buf,100);
    }
}



