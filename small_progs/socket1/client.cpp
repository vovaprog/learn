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

#include "message.h"
#include "util.h"

int client()
{
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_fd<0)
    {
        printf("socket failed!\r\n");
        return -1;
    }
    
    struct sockaddr_in remoteaddr;
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remoteaddr.sin_port = htons(7000);
    if(connect(socket_fd, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr))!=0)    
    {
        printf("connect failed!\r\n");
        close(socket_fd);
        return -1;                
    }
    
    Message msg;
    msg.id = 1;
    
    printf("request id: %llu\n",msg.id);
    
    if(writeBytes(socket_fd, (char*)&msg, sizeof(Message))!=0)
    {
        printf("writeBytes failed\n");
        close(socket_fd);
        return -1;
    }
    
    if(readBytes(socket_fd, (char*)&msg, sizeof(Message))!=0)
    {
        printf("readBytes failed\n");
        close(socket_fd);
        return -1;        
    }
    
    printf("response id: %llu\n",msg.id);
    
    return 0;    
}


int main()
{
    client();

    return 0;
}



