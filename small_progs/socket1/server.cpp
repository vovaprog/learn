#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "message.h"
#include "util.h"
#include "TransferRingBuffer.h"

int sockfd = -1;

void sig_int_handler(int i)
{
    printf("sig int handler\n");

    if(sockfd > 0)
    {
        close(sockfd);
    }

    exit(-1);
}

bool initSocket()
{
    signal(SIGINT, sig_int_handler);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("socket failed\n");
        return false;
    }

    int enable = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
    {
        printf("setsockopt failed\n");
        close(sockfd);
        return false;
    }

    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(7000);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in)) != 0)
    {
        printf("bind failed: %s\r\n", strerror(errno));
        close(sockfd);
        return false;
    }

    if(listen(sockfd, 1000) != 0) //length of queue of pending connections
    {
        printf("listen failed!\r\n");
        close(sockfd);
        return false;
    }
    
    return true;
}


const int BUF_SIZE = 1000000;
unsigned char buf[BUF_SIZE];

inline void checkBuf()
{
    for(int i=0;i<BUF_SIZE-1;++i)
    {
        if(!(buf[i] == 255 && buf[i+1]==0 || buf[i] + 1 == buf[i+1]))
        {
            printf("invalid data\n");
            exit(-1);
        }
    }
}

static void* threadEntry(void *arg)
{
    int clientSocket = *static_cast<int*>(arg);
    free(arg);
    
    while(true)
    {                
        if(readBytes(clientSocket, (char*)buf, BUF_SIZE)!=BUF_SIZE)
        {
            printf("readBytes failed\n");
            return nullptr;
        }

        if(writeBytes(clientSocket, (char*)buf, BUF_SIZE)!=BUF_SIZE)
        {
            printf("writeBytes failed\n");
            return nullptr;
        }
    }
}

static void* threadEntry2(void *arg)
{
    int clientSocket = *static_cast<int*>(arg);
    free(arg);
    
    int dataSize = 0;
    
    while(true)
    {
        int rd = read(clientSocket, buf + dataSize, BUF_SIZE - dataSize);
        
        if(rd<=0)
        {
            printf("readBytes failed\n");
            return nullptr;            
        }
        
        dataSize += rd;

        int wr = write(clientSocket, buf, dataSize);
        
        if(wr<=0)
        {
            printf("writeBytes failed\n");
            return nullptr;
        }
        
        dataSize -= wr;
        memmove(buf, buf+wr, dataSize); 
    }
}


static void* threadEntry3(void *arg)
{
    int clientSocket = *static_cast<int*>(arg);
    free(arg);
    
    int dataSize = 0;
    
    TransferRingBuffer tBuf(BUF_SIZE);
    
    while(true)
    {
        void *data;
        int size;
        tBuf.startWrite(data, size);
        
        int rd = read(clientSocket, data, size);
        
        if(rd<=0)
        {
            printf("readBytes failed\n");
            return nullptr;            
        }
        
        tBuf.endWrite(rd);

        tBuf.startRead(data, size);

        int wr = write(clientSocket, data, size);
        
        if(wr<=0)
        {
            printf("writeBytes failed\n");
            return nullptr;
        }
        
        tBuf.endRead(wr);
    }
}


bool server()
{
    if(!initSocket())
    {
        return false;
    }

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(sockaddr_in);    
    
    while(true)
    {
        int clientSocket = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

        if(clientSocket < 0)
        {
            printf("accept failed\r\n");
        }
        else
        {
            pthread_t th;
            int *pClientSocket = (int*)malloc(sizeof(int));
            *pClientSocket = clientSocket;
            
            //pthread_create(&th, nullptr, threadEntry, pClientSocket);
            //pthread_create(&th, nullptr, threadEntry2, pClientSocket);
            pthread_create(&th, nullptr, threadEntry3, pClientSocket);
        }
    }
}

int main()
{
    server();

    return 0;
}
