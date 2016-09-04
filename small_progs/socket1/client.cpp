#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include "message.h"
#include "util.h"
#include "ExecsPerSecond.h"

//no difference in speed - 127.0.0.1 or local ip address

int clientConnect()
{
    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remoteaddr.sin_port = htons(7000);
    
    Message msg;
    msg.id = 1;
    
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd < 0)
    {
        printf("socket failed!\r\n");
        return -1;
    }

    if(connect(socket_fd, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr)) != 0)
    {
        printf("connect failed!\r\n");
        close(socket_fd);
        return -1;
    }      
    
    return socket_fd;
}

int client1()
{
    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //remoteaddr.sin_addr.s_addr = inet_addr("192.168.1.145");
    remoteaddr.sin_port = htons(7000);
    
    Message msg;
    msg.id = 1;
    
    ExecsPerSecond execCounter;
    
    for(int i=0;;++i)
    {    
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
        if(socket_fd < 0)
        {
            printf("socket failed!\r\n");
            return -1;
        }
    
        if(connect(socket_fd, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr)) != 0)
        {
            printf("connect failed!\r\n");
            close(socket_fd);
            return -1;
        }
        
        //printf("request id: %llu\n", msg.id);
    
        if(writeBytes(socket_fd, (char*)&msg, sizeof(Message)) != sizeof(Message))
        {
            printf("writeBytes failed\n");
            close(socket_fd);
            return -1;
        }
    
        if(readBytes(socket_fd, (char*)&msg, sizeof(Message)) != sizeof(Message))
        {
            printf("readBytes failed\n");
            close(socket_fd);
            return -1;
        }
    
        //printf("response id: %llu\n", msg.id);
        
        close(socket_fd);
        
        execCounter.incAndPrint();
    }

    return 0;
}

int client2()
{        
    int socket_fd = clientConnect();
    
    ExecsPerSecond execCounter;
    
    Message msg;
    msg.id = 1;    
    
    for(int i=0;;++i)
    {    
        //printf("request id: %llu\n", msg.id);
    
        if(writeBytes(socket_fd, (char*)&msg, sizeof(Message)) != sizeof(Message))
        {
            printf("writeBytes failed\n");
            close(socket_fd);
            return -1;
        }
    
        if(readBytes(socket_fd, (char*)&msg, sizeof(Message)) != sizeof(Message))
        {
            printf("readBytes failed\n");
            close(socket_fd);
            return -1;
        }
    
        //printf("response id: %llu\n", msg.id);        
        
        execCounter.incAndPrint();
    }
    
    close(socket_fd);

    return 0;
}

const int BUF_SIZE = 1000000;   
unsigned char buf[BUF_SIZE];

inline void checkBuf(int &readCounter)
{
    for(int i=0;i<BUF_SIZE;++i)
    {
        if(buf[i] != readCounter)
        {
            printf("invalid data %d : %d\n",(int)buf[i],(int)readCounter);
            exit(-1);            
        }
        readCounter = ((readCounter + 1) & 0xff);
    }    
}

int client3()
{
    int socket_fd = clientConnect();
    
    ExecsPerSecond execCounter(100000);
    
    int charCounter = 0, readCounter = 0;
    
    while(true)
    {        
        for(int i=0;i<BUF_SIZE;++i)
        {
            buf[i]=charCounter;
            charCounter = ((charCounter + 1) & 0xff);            
        }
        
        if(writeBytes(socket_fd, (char*)buf, BUF_SIZE) != BUF_SIZE)
        {
            printf("writeBytes failed\n");
            close(socket_fd);
            return -1;
        }
        
        if(readBytes(socket_fd, (char*)buf, BUF_SIZE)!=BUF_SIZE)
        {
            printf("readBytes failed\n");
            close(socket_fd);
            return -1;            
        }

        //checkBuf(readCounter);
        
        execCounter.addAndPrint(BUF_SIZE);       
    }
    
    close(socket_fd);
    
    return 0;
}

int main()
{
    //client1();
    //client2();
    client3();

    return 0;
}



