#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MULTICAST_PORT 12345
#define MULTICAST_GROUP "225.0.0.37"

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd < 0)
    {
        perror("socket failed");
        exit(-1);
    }

    int enable = 1;

    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
    {
        perror("setsockopt SO_REUSEADDR failed");
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(MULTICAST_PORT);


    if(bind(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if(setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt");
        exit(1);
    }

    char msgbuf[1000];
    
    while(1)
    {
        socklen_t addrlen;
        addrlen = sizeof(addr);
        int bytesRead = recvfrom(fd, msgbuf, sizeof(msgbuf), 0, (struct sockaddr *) &addr, &addrlen);
        if(bytesRead < 0)
        {
            perror("recvfrom");
            exit(1);
        }
        msgbuf[sizeof(msgbuf) - 1] = 0;
        puts(msgbuf);
    }
}
