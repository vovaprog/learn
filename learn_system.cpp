#include "learn_system.h"

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <fcntl.h>

using namespace std;

void learn_system1()
{
    int pipe_fds[2],read_fd,write_fd;
    
    if(pipe(pipe_fds)!=0)
    {
        cout << "pipe failed!"<<endl;
    }
    
    read_fd=pipe_fds[0];
    write_fd=pipe_fds[1];
    
    pid_t result=fork();
    
    if(result==0)
    {
        cout <<"child"<<endl;
        
        close(read_fd);
        
        FILE* ostream=fdopen(write_fd,"w");
        
        char buf[1000];
        
        strcpy(buf,"works   ");
        
        while(true)
        {
            //fputs(buf,ostream);
            fprintf(ostream,"%s",buf);
            cout <<"writing"<<endl;
            
            //write(write_fd,buf,strlen(buf));
            sleep(1);
        }        
    }
    else if(result>0)
    {
        cout <<"parent"<<endl;
        
        close(write_fd);
        
        FILE* istream=fdopen(read_fd,"r");
        
        char buf[1000];
        
        while(true)
        {
            cout <<"reading"<<endl;
            int bytesRead = fread(buf,1,10,istream);
            cout <<"after read"<<endl;
            
            buf[bytesRead]=0;
            if(bytesRead!=0)
            {                
                printf("%s\n",buf);
                //fputs(buf,stdout);
                fflush(stdout);
            }
            else
            {
                cout <<"fread failed!"<<endl;
                return;
            }
                        
            /*int bytesRead = read(read_fd,buf,10-1);            
            buf[bytesRead]=0;
            printf(buf);*/
            fflush(stdout);
        }
        
                 
//        int result = execlp("echo","echo","hello!","world!",NULL);
//        cout <<"exec failed! "<<result<<endl;
    }
    else
    {
        cout <<"error!"<<endl;    
    }
}

void learn_named_pipe()
{
    printf("pipe buf: %d\n",(int)PIPE_BUF);
    
    if(mkfifo("./mypipe1",0700)!=0)
    {
        printf("mkfifo failed\n");
        return;
    }
    
    int fifo_fd=open("./mypipe1",O_WRONLY);
    
    if(fifo_fd<0)
    {
        printf("open failed\n");
        return;
    }
    
    char c='!';
    
    for(int i=0;i<100000;i++)
    {
        fflush(stdout);
        if(write(fifo_fd,&c,1)!=1)
        {
            printf("write failed\n");
            return;
        }
        printf("%d ",i);
        fflush(stdout);
    }    
}

void learn_system()
{
    //learn_system1();
    
    learn_named_pipe();
}
