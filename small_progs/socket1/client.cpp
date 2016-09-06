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

#include <NetworkUtils.h>
#include <IncPerSecond.h>
#include <TransferRingBuffer.h>

static int sock = -1;

void sig_int_handler(int i)
{
    printf("sig int handler\n");

    if(sock > 0)
    {
        close(sock);
    }

    exit(-1);
}


const int BUF_SIZE = 1000000;
unsigned char buf[BUF_SIZE];
unsigned char buf_write[BUF_SIZE];
unsigned char buf_read[BUF_SIZE];


void checkBuffer(unsigned char *buf, int size, int &readCounter)
{
    for(int i = 0; i < size; ++i)
    {
        if(buf[i] != readCounter)
        {
            printf("invalid data %d != %d   (i=%d)\n", (int)buf[i], readCounter, i);
            for(int j = i - 10; j < i + 10; ++j)
            {
                if(j >= 0 && j < size)
                {
                    printf("buf[%d] = %d\n", j, buf[j]);
                }
            }
            exit(-1);
        }
        readCounter = ((readCounter + 1) & 0xff);
    }
}


char recvBuf[BUF_SIZE];

int client(const char *addr, bool withCheck)
{
    sock = socketConnect(addr, 7000);
    if(!setNonBlock(sock))
    {
        printf("setNonBlock failed\n");
        close(sock);
        return -1;
    }

    IncPerSecond incCounter(1000000);

    int charCounter = 0, readCounter = 0;

    TransferRingBuffer sendBuf(BUF_SIZE);


    while(true)
    {
        void *data;
        int size;

        if(sendBuf.startWrite(data, size))
        {
            for(int i = 0; i < size; ++i)
            {
                ((unsigned char*)data)[i] = charCounter;
                charCounter = ((charCounter + 1) & 0xff);
            }
            sendBuf.endWrite(size);
        }

        if(sendBuf.startRead(data, size))
        {
            int wr = write(sock, data, size);
            if(wr <= 0)
            {
                if(errno != EWOULDBLOCK && errno != EAGAIN)
                {
                    printf("write failed: %s\n", strerror(errno));
                    close(sock);
                    return -1;
                }
            }
            else
            {
                sendBuf.endRead(wr);
            }
        }

        int rd = read(sock, recvBuf, size);
        if(rd <= 0)
        {
            if(errno != EWOULDBLOCK && errno != EAGAIN)
            {
                if(rd == 0 && errno == 0)
                {
                    printf("disconnected\n");
                    close(sock);
                    return -1;
                }
                else
                {
                    printf("read failed: %s\n", strerror(errno));
                    close(sock);
                    return -1;
                }
            }
        }
        else
        {
            if(withCheck)
            {
                checkBuffer((unsigned char*)recvBuf, rd, readCounter);
            }

            incCounter.addAndPrint(rd);
        }
    }

    close(sock);

    return 0;
}


int main(int argc, char** argv)
{
    signal(SIGINT, sig_int_handler);

    const char * addr = "127.0.0.1";
    bool withCheck = false;

    if(argc >= 2)
    {
        addr = argv[1];
    }
    if(argc >= 3 && strcmp(argv[2], "check") == 0)
    {
        withCheck = true;
        printf("running with check\n");
    }

    client(addr, withCheck);

    return 0;
}



