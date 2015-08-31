#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

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
    
    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(80);
    
    //inet_pton(AF_INET,addressInfo->ai_addr,&serv_addr.sin_addr);
    
    if(connect(socket_fd,addressInfo->ai_addr,sizeof(serv_addr))!=0)
    {
        printf("connect failed!\r\n");
        
        close(socket_fd);
        return -1;
    }
    
    char *httpRequest="GET / HTTP/1.1\nhost: www.ya.ru\n\n";
    
    if(write(socket_fd,httpRequest,strlen(httpRequest))!=strlen(httpRequest))
    {
        printf("write failed!\r\n");
        
        close(socket_fd);        
        return -1;
    }
    
    char responseBuf[10000];
    
    while(1)
    {
        int bytesRead = read(socket_fd,responseBuf,sizeof(responseBuf-1));
        
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
        
        //printf("[[[");
        printf(responseBuf);
        
        
        int newLineCounter=0;
        for(int i=bytesRead;i>=0;--i)
        {
            if(responseBuf[i]=='\n')
            {
                newLineCounter++;    
            }
            else if(responseBuf[i]!='\r')
            {
                break;    
            }
        }
        
        if(newLineCounter>=2)
        {
            break;    
        }
    }

    close(socket_fd);    
    return 0;
}


