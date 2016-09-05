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
#include "TransferRingBuffer.h"

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

const int BUF_SIZE = 1000000;
unsigned char buf[BUF_SIZE];
unsigned char buf_write[BUF_SIZE];
unsigned char buf_read[BUF_SIZE];

inline void checkBuf(unsigned char *buf, int &readCounter, int count = BUF_SIZE)
{
    for(int i=0;i<count;++i)
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

        //checkBuf(buf, readCounter);
        
        execCounter.addAndPrint(BUF_SIZE);       
    }
    
    close(socket_fd);
    
    return 0;
}

int client4()
{
    int socket_fd = clientConnect();
    
    ExecsPerSecond execCounter(100000);
    
    int charCounter = 0, readCounter = 0;
    int startFill = 0;
    
    while(true)
    {        
        for(int i=startFill;i<BUF_SIZE;++i)
        {
            buf_write[i]=charCounter;
            charCounter = ((charCounter + 1) & 0xff);
        }
        
        int wr = write(socket_fd, buf_write, BUF_SIZE);
        
        if(wr <= 0)
        {
            printf("writeBytes failed\n");
            close(socket_fd);
            return -1;            
        }
        
        if(wr < BUF_SIZE)
        {
            memmove(buf_write, buf_write + wr, BUF_SIZE - wr);
        }
        startFill = BUF_SIZE - wr;
        
        int rd = read(socket_fd, buf_read, wr);
        
        if(rd <= 0)
        {
            printf("readBytes failed\n");
            close(socket_fd);
            return -1;
        }
        
        //checkBuf(buf_read, readCounter, rd);
        
        execCounter.addAndPrint(rd);       
    }
    
    close(socket_fd);
    
    return 0;
}

int client5()
{
    int socket_fd = clientConnect();
    
    ExecsPerSecond execCounter(100000);
    
    int charCounter = 0, readCounter = 0;
    int startFill = 0;
    
    TransferRingBuffer tBuf(BUF_SIZE);
    
    while(true)
    {        
        void *data;
        int size;
        tBuf.startWrite(data, size);        
        
        for(int i=0;i<size;++i)
        {
            ((unsigned char*)data)[i]=charCounter;
            charCounter = ((charCounter + 1) & 0xff);
        }
        
        int wr = write(socket_fd, data, size);
        
        if(wr <= 0)
        {
            printf("writeBytes failed\n");
            close(socket_fd);
            return -1;            
        }
        
        tBuf.endWrite(wr);
        
        
        tBuf.startRead(data, size);
        
        int rd = read(socket_fd, data, size);
        
        if(rd <= 0)
        {
            printf("readBytes failed\n");
            close(socket_fd);
            return -1;
        }                
        
        //checkBuf((unsigned char*)data, readCounter, rd);
        
        tBuf.endRead(rd);
        
        execCounter.addAndPrint(rd);       
    }
    
    close(socket_fd);
    
    return 0;
}

int main()
{
    //client3();
    //client4();
    client5();

    return 0;
}



