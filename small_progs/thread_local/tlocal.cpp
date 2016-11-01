
int thread_local_accum(int x)
{
    thread_local int accum = 0;    
    
    accum += x;
    
    return accum;
}


int tLocal(int x)
{
    thread_local int accum = 0;    
    
    for(long long int i=0;i<200000000;++i)
    {
        accum += x + i;
    }
    
    return accum;
}

int simple(int x)
{
    thread_local int accum = 0;    
    
    for(long long int i=0;i<200000000;++i)
    {
        accum += x + i;
    }
    
    return accum;
}
