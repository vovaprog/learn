#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void writeMessage(mqd_t mq)
{
    const char *message="hello, world!";
    int messagePriority=0;
    
    if(mq_send(mq,message,strlen(message)+1,messagePriority)!=0)
    {
        perror("mq_send");
        return;
    }        
}

void readMessage(mqd_t mq)
{
    char buf[100];
    unsigned int messagePriority;
    
    int numberOfBytes = mq_receive(mq,buf,100,&messagePriority);
    
    if(numberOfBytes==-1)
    {
        perror("mq_receive");
        return;
    }
    
    printf("mq_receive: <%s>\n",buf);
}

void learnMessageQueue()
{
    struct mq_attr attr;  
    attr.mq_flags = 0;  
    attr.mq_maxmsg = 5;  
    attr.mq_msgsize = 100;  
    attr.mq_curmsgs = 0;      
    
    const char *queueName="/MyMessageQueue";
    
    mqd_t mq = mq_open(queueName,O_CREAT | O_RDWR,S_IRWXU | S_IRWXG, &attr);
    
    if(mq==-1)
    {
        perror("mq_open");
        return;
    }
    
    writeMessage(mq);
    readMessage(mq);
    
    if(mq_close(mq)!=0)
    {
        perror("mq_close");
        return;
    }    
    
    if(mq_unlink(queueName)!=0)
    {
        perror("mq_unlink");
        return;
    }
}
