#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>


int main()
{
    printf("hello, world!\n");

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        printf("socket failed: %s\n", strerror(errno));
        return -1;
    }

    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remoteaddr.sin_port = htons(7000);

    if(connect(sock, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr)) != 0)
    {
        printf("connect failed: %s\n", strerror(errno));
        close(sock);
        return -1;
    }

    const char *ptr = "GET / HT";

    int bytesWritten = write(sock, ptr, strlen(ptr));

    printf("bytesWritten: %d\n", bytesWritten);

    exit(-1);

    return 0;
}
