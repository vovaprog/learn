#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int getExecutableName(char *name,int nameSize);

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };


int createSemaphore()
{
    const int maxExeFileName=1000;
    char exeFileName[maxExeFileName];  
    
    if(getExecutableName(exeFileName,maxExeFileName)!=0)
    {
        printf("getExecutableName failed\n");
        return -1;
    }
    
    printf("exe: <%s>\n",exeFileName);
    
    //key_t ipc_key = ftok(exeFileName,33);
    
    key_t ipc_key = 553745195;
    
    if(ipc_key==-1)
    {
        printf("ftok failed %s\n",strerror(errno));
        return -1;
    }
     
    printf("ipc_key: %d\n",ipc_key);
    
    int sem_id = semget(ipc_key,1,IPC_CREAT /*| 0660*/);
    
    if(sem_id==-1)
    {
        printf("semget failed\n");
        return -1;
    }
    
    printf("sem id: %d\n",sem_id);
    
    return sem_id;    
}

void removeSemaphore(int sem_id)
{
    union semun ignored_argument;
    if(semctl (sem_id, 1, IPC_RMID, ignored_argument)==-1)
    {
        printf("semctl failed\n");        
    }
}

int semaphoreWait(int semid)
{
    struct sembuf operations[1];
    /* Use the first (and only) semaphore. */
    operations[0].sem_num = 0;
    /* Decrement by 1. */
    operations[0].sem_op = -1;
    /* Permit undo'ing. */
    operations[0].sem_flg = 0; //SEM_UNDO;
    if(semop (semid, operations, 1)==-1)
    {
        printf("semop failed\n");
        return -1;        
    }
    return 0;
}
/* Post to a binary semaphore: increment its value by 1.
This returns immediately. */
int semaphorePost(int semid)
{
    struct sembuf operations[1];
    /* Use the first (and only) semaphore. */
    operations[0].sem_num = 0;
    /* Increment by 1. */
    operations[0].sem_op = 1;
    /* Permit undo'ing. */
    operations[0].sem_flg = 0;//SEM_UNDO;
    if( semop (semid, operations, 1)==-1)
    {
        printf("semop failed\n");
        return -1;
    }
    
    return 0;
}

void semaphoreGetCount(int semid)
{
    int count = semctl(semid,0,GETVAL);    
    printf("count: %d\n",count);
}

void learnProcessSemaphores()
{
    int sem_id = createSemaphore();    
    
    /*semaphorePost(sem_id);*/
    semaphoreGetCount(sem_id);
    /*sleep(1000);*/
    semaphoreWait(sem_id);
    semaphoreGetCount(sem_id);
}

