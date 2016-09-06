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

#include <NetworkUtils.h>
#include <TransferRingBuffer.h>

static int sockfd = -1;

void sig_int_handler(int i)
{
    printf("sig int handler\n");

    if(sockfd > 0)
    {
        close(sockfd);
    }

    exit(-1);
}


const int BUF_SIZE = 1000000;
unsigned char buf[BUF_SIZE];
bool checkData = false;

inline void checkBuffer(void *buffer, int size)
{
    unsigned char *buf = static_cast<unsigned char*>(buffer);

    for(int i = 0; i < size - 1; ++i)
    {
        if(!(buf[i] == 255 && buf[i + 1] == 0 || buf[i] + 1 == buf[i + 1]))
        {
            printf("invalid data\n");
            exit(-1);
        }
    }
}


static void* clientThreadEntry(void *arg)
{
    int clientSocket = *static_cast<int*>(arg);
    free(arg);

    int dataSize = 0;

    TransferRingBuffer tBuf(BUF_SIZE);

    while(true)
    {
        void *data;
        int size;

        if(tBuf.startWrite(data, size))
        {
            int rd = read(clientSocket, data, size);
    
            if(rd <= 0)
            {
                if(rd == 0)
                {
                    printf("client disconnected\n");
                }
                else
                {
                    printf("readBytes failed: %s\n", strerror(errno));
                }
                close(clientSocket);
                return nullptr;
            }
    
            tBuf.endWrite(rd);
        }


        if(tBuf.startRead(data, size))
        {
            if(checkData)
            {
                checkBuffer(data, size);
            }
    
            int wr = write(clientSocket, data, size);
    
            if(wr <= 0)
            {
                printf("writeBytes failed\n");
                close(clientSocket);
                return nullptr;
            }
    
            tBuf.endRead(wr);
        }
    }
}


bool server()
{
    sockfd = socketListen(7000);
    if(sockfd <= 0)
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

            pthread_create(&th, nullptr, clientThreadEntry, pClientSocket);
        }
    }
}


int main()
{
    signal(SIGINT, sig_int_handler);

    server();

    return 0;
}
