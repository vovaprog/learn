#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

void learnSockets()
{
    int sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    int buf;
    socklen_t bufSize = sizeof(buf);

    if(getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &buf, &bufSize) != 0)
    {
        printf("getsockopt failed\n");
        return;
    }

    printf("send buf: %d\n",buf);
        
    if(getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &buf, &bufSize) != 0)
    {
        printf("getsockopt failed\n");
        return;
    }

    printf("recv buf: %d\n",buf);

    close(sock);
}


