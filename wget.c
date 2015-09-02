#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "wget.h"

int wget()
{
    struct addrinfo *addressInfo;
    
    
    if(getaddrinfo("www.yandex.ru","80",0,&addressInfo)!=0)
    {
        printf("getaddrinfo failed!\r\n");
        return -1;
    }
    
    
    
    
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_fd<0)
    {
        printf("socket failed!\r\n");
        return -1;
    }
    
    
    
    bool connected=false;
    
    for(struct addrinfo *p = addressInfo; p != NULL; p = p->ai_next) 
    {        
        if(connect(socket_fd,p->ai_addr,p->ai_addrlen)==0)
        {
            connected=true;
            break;
        }
        else            
        {
            printf("connect failed: %s\r\n",strerror(errno));            
            continue;
        }
    }
    
    if(!connected)
    {
        close(socket_fd);
        return -1;        
    }
    
    char *httpRequest="GET / HTTP/1.1\nhost: www.yandex.ru\n\n";
    
    if(write(socket_fd,httpRequest,strlen(httpRequest))!=strlen(httpRequest))
    {
        printf("write failed!\r\n");
        
        close(socket_fd);        
        return -1;
    }
    
#define RESPONSE_SIZE 10000    
    char responseBuf[RESPONSE_SIZE];
    
    while(1)
    {
        int bytesRead = read(socket_fd,responseBuf,RESPONSE_SIZE-1);
        
        if(bytesRead < 0)
        {
            printf("read failed!\r\n");
            
            close(socket_fd);            
            return -1;
        }
        else if(bytesRead==0)
        {
            break;    
        }
        
        responseBuf[bytesRead]=0;
        
        printf("[ ");
        printf(responseBuf);
        printf(" ]\n");
    }

    close(socket_fd);    
    return 0;
}


