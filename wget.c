#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "wget.h"

/*
клиент порядок вызовов:
socket
gethostbyname/getaddrinfo
connect
write/send
read/recv
close

The only difference between send() and write(2) is the
presence of flags.  With a zero flags argument, send() is equivalent to write(2).

*/

int wget()
{    
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_fd<0)
    {
        printf("socket failed!\r\n");
        return -1;
    }
 
    
    int useGetHostByName=1;
    
    if(useGetHostByName)
    {       
        struct sockaddr_in name;
        struct hostent* hostinfo;
        
        name.sin_family = AF_INET;
        
        hostinfo = gethostbyname ("www.yandex.ru");
        
        if (hostinfo == NULL)
        {
            return -1;
        }
        else
        {
            name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
        }
        
        name.sin_port = htons (80);
        
        
        if (connect (socket_fd, (struct sockaddr*) &name, sizeof (struct sockaddr_in)) != 0) 
        {
            printf("connect failed!\r\n");
            close(socket_fd);
            return -1;                
        }
    }
    else
    {    
        struct addrinfo *addressInfo;
        
        
        if(getaddrinfo("www.yandex.ru","80",0,&addressInfo)!=0)
        {
            printf("getaddrinfo failed!\r\n");
            return -1;
        }
        
        
        int connected=0;
        
        for(struct addrinfo *p = addressInfo; p != NULL; p = p->ai_next) 
        {        
            if(connect(socket_fd,p->ai_addr,p->ai_addrlen)==0)
            {
                connected=1;
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
    }
    
    
    
    char *httpRequest="GET / HTTP/1.1\nhost: www.yandex.ru\n\n";
    
    if(send(socket_fd,httpRequest,strlen(httpRequest),0)!=strlen(httpRequest))
    //if(write(socket_fd,httpRequest,strlen(httpRequest))!=strlen(httpRequest))
    {
        printf("write failed!\r\n");
        
        close(socket_fd);        
        return -1;
    }
    
#define RESPONSE_SIZE 10000    
    char responseBuf[RESPONSE_SIZE];
    
    while(1)
    {
        //int bytesRead = read(socket_fd,responseBuf,RESPONSE_SIZE-1);
        int bytesRead = recv(socket_fd,responseBuf,RESPONSE_SIZE-1,0);
        
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
        
        printf("[ %s ]\n",responseBuf);
    }

    close(socket_fd);    
    return 0;
}


