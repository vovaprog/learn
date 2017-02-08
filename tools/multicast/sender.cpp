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
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    addr.sin_port = htons(MULTICAST_PORT);

    while(1)
    {
    	const char *message = "hello, world!";
    	
        if(sendto(fd, message, strlen(message), 0, (struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            perror("sendto");
            exit(1);
        }
        sleep(1);
    }
}
