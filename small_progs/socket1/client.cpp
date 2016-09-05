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

inline void checkBuf(unsigned char *buf, int &readCounter, int count = BUF_SIZE)
{
    for(int i = 0; i < count; ++i)
    {
        if(buf[i] != readCounter)
        {
            printf("invalid data %d : %d\n", (int)buf[i], (int)readCounter);
            exit(-1);
        }
        readCounter = ((readCounter + 1) & 0xff);
    }
}


int client(const char *addr, bool checkBuffer)
{
    sock = socketConnect(addr, 7000);

    IncPerSecond incCounter(1000000);

    int charCounter = 0, readCounter = 0;
    int startFill = 0;

    TransferRingBuffer tBuf(BUF_SIZE);

    while(true)
    {
        void *data;
        int size;
        tBuf.startWrite(data, size);

        for(int i = 0; i < size; ++i)
        {
            ((unsigned char*)data)[i] = charCounter;
            charCounter = ((charCounter + 1) & 0xff);
        }

        int wr = write(sock, data, size);

        if(wr <= 0)
        {
            printf("writeBytes failed\n");
            close(sock);
            return -1;
        }

        tBuf.endWrite(wr);


        tBuf.startRead(data, size);

        int rd = read(sock, data, size);

        if(rd <= 0)
        {
            printf("readBytes failed\n");
            close(sock);
            return -1;
        }

        if(checkBuffer)
        {
            checkBuf((unsigned char*)data, readCounter, rd);
        }

        tBuf.endRead(rd);

        incCounter.addAndPrint(rd);
    }

    close(sock);

    return 0;
}

int main(int argc, char** argv)
{
    signal(SIGINT, sig_int_handler);

    const char * addr = "127.0.0.1";

    if(argc >= 2)
    {
        addr = argv[1];
    }

    client(addr, false);

    return 0;
}



