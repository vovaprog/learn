#include "http_server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/*
Вызовы socket на сервере:
socket
bind
listen
accept
read/recv
write/send
close client socket
close server socket
*/

int sockfd=-1;

void sig_int_handler(int i)
{ 
    printf("sig int handler\r\n");
    
    if(sockfd>0)
    {
        close(sockfd);
    }
}

void getResponse(char *request,char *response)
{
    char url[1000];
    
    sscanf(request,"GET %s HTTP",url);
    
    printf("{ %s }\r\n",url);
    
    
    strcpy(response,"HTTP/1.1 200 Ok\r\n\r\n");
    
    
    
    char *html;
    
    if(strcmp(url,"/hello")==0)
    {
        html=(char*)"<h1>hello</h1><br/><a href='/'>back</a>";
    }
    else if(strcmp(url,"/world")==0)
    {
        html=(char*)"<h1>world</h1><br/><a href='/'>back</a>";
    }
    else
    {
        html=(char*)"<h2>hello, world!</h2><a href='/hello'>hello</a><br/><a href='/world'>world</a>";
    }
    
    strcat(response,html);
}


bool http_server()
{
    signal(SIGINT,sig_int_handler);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd<0)
    {
        printf("socket failed\r\n");
        return false;        
    }
    
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;
    
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);  
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in)) != 0)
    {
        printf("bind failed: %s\r\n",strerror(errno));            
        close(sockfd);
        return false;
    }
    
    if(listen(sockfd,1000)!=0)
    {
        printf("listen failed!\r\n");
        close(sockfd);
        return false;
    }
    
    int bufSize=1000;
    char buf[bufSize];
    
    while(true)
    {
        int client_socket_fd = accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);

        if(client_socket_fd<0)
        {
            printf("accept failed\r\n");
            close(sockfd);
            return false;
        }
        
        int numBytes = recv(client_socket_fd,buf,bufSize-1,0);
        
        if(numBytes<=0)
        {
            printf("recv failed\r\n");
            return false;
        }
        
        buf[numBytes]=0;
        
        printf("[ %s ]\r\n",buf);
        
        
        char response[bufSize];
        
        getResponse(buf,response);
        
        
        if(send(client_socket_fd,response,strlen(response),0)!=(ssize_t)strlen(response))
        {
            printf("send failed\r\n");
            return false;
        }
        
        close(client_socket_fd);        
    }
    
    return true;    
}


