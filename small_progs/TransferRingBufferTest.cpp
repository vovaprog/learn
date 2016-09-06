#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRANSFER_RING_BUFFER_DEBUG
#include "../tools/TransferRingBuffer.h"
#undef TRANSFER_RING_BUFFER_DEBUG


void checkBuffer1(unsigned char *buf, int size, unsigned int &readCounter)
{
    for(int i = 0; i < size; ++i)
    {
        if(buf[i] != readCounter)
        {
            printf("invalid data %d != %d   (%d)\n", (int)buf[i], (int)readCounter, i);
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

void checkBuffer2(void *buffer, int size)
{
    unsigned char *buf = static_cast<unsigned char*>(buffer);

    for(int i = 0; i < size - 1; ++i)
    {
        if(!((buf[i] == 255 && buf[i + 1] == 0) || buf[i] + 1 == buf[i + 1]))
        {
            printf("invalid data:   buf[%d]=%d   buf[%d]=%d\n", i, (int)buf[i], i + 1, (int)buf[i + 1]);
            for(int j = i - 10; j < i + 10; ++j)
            {
                if(j >= 0 && j < size)
                {
                    printf("buf[%d] = %d\n", j, buf[j]);
                }
            }

            exit(-1);
        }
    }
}


void testRing()
{
    TransferRingBuffer sendBuf(100);

    unsigned int charCounter = 0, readCounter = 0;

    srand(time(NULL));

    while(true)
    {
        void *data;
        int size;

        printf("-----------------\n");
        sendBuf.printInfo();
        if(sendBuf.startWrite(data, size))
        {
            int rnd = rand() % size + 1;
            for(int i = 0; i < rnd; ++i)
            {
                ((unsigned char*)data)[i] = charCounter;
                charCounter = ((charCounter + 1) & 0xff);
            }
            sendBuf.endWrite(rnd);
        }

        sendBuf.printInfo();
        if(sendBuf.startRead(data, size))
        {
            int rnd = rand() % size + 1;
            checkBuffer1((unsigned char*)data, rnd, readCounter);
            checkBuffer2((unsigned char*)data, rnd);

            sendBuf.endRead(rnd);
            sendBuf.printInfo();
        }
    }
}

int main()
{
    testRing();
    return 0;
}

