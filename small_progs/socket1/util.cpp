#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

#include "util.h"

int readBytes(int fd, char *buf, int numberOfBytes)
{
    int bytesRead = 0;
    while(bytesRead < numberOfBytes)
    {
        //int curBytes = recv(fd, buf + bytesRead, numberOfBytes - bytesRead, 0);
        int curBytes = read(fd, buf + bytesRead, numberOfBytes - bytesRead);
        if(curBytes < 0)
        {
            return -1;
        }
        else if(curBytes == 0)
        {
            return bytesRead;
        }
        bytesRead += curBytes;
    }
    return bytesRead;
}

int writeBytes(int fd, char *buf, int numberOfBytes)
{
    int bytesWritten = 0;
    while(bytesWritten < numberOfBytes)
    {
        int curBytes = write(fd, buf + bytesWritten, numberOfBytes - bytesWritten);
        if(curBytes <= 0)
        {
            return -1;
        }
        bytesWritten += curBytes;
    }
    return bytesWritten;
}
