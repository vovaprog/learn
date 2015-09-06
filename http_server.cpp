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
    
    
    sprintf(response,"HTTP/1.1 200 Ok\r\nContent-Length: %d\r\n\r\n%s",(int)strlen(html),html);
    
    //strcat(response,html);
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
    
    int enable = 1;
    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0 )
    {
        printf("setsockopt failed\r\n");
        close(sockfd);
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


bool http_server_select()
{
    signal(SIGINT,sig_int_handler);
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    printf("sockfd: %d\r\n",sockfd);
    
    if(sockfd<0)
    {
        printf("socket failed\r\n");
        return false;        
    }
    
    int enable = 1;
    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0 )
    {
        printf("setsockopt failed\r\n");
        close(sockfd);
        return false;
    }    
    
    
    struct sockaddr_in serv_addr;//,cli_addr;
    //socklen_t clilen;
    
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
    
    fd_set select_read_fds;
    int max_select_fd;
    
    const int max_clients = 30;
    int client_socket[max_clients];     
        
    memset(client_socket,0,max_clients * sizeof(int));
    
    while(true)
    {
        FD_ZERO(&select_read_fds);
        FD_SET(sockfd, &select_read_fds);
        
        max_select_fd = sockfd;
        
        for (int i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            int sd = client_socket[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
            {
                FD_SET( sd , &select_read_fds);
            }
             
            //highest file descriptor number, need it for the select function
            if(sd > max_select_fd)
            {
                max_select_fd = sd;
            }
        }        

        printf("before select\r\n");
        int selectResult = select( max_select_fd + 1 , &select_read_fds , NULL , NULL , NULL);
        
        if(selectResult<0)
        {
            printf("select failed\r\n");
            close(sockfd);
            return false;
        }
        
        if(selectResult>0)
        {
            int new_socket=-1;
            
            if (FD_ISSET(sockfd, &select_read_fds)) 
            {
                
                struct sockaddr_in address;
                socklen_t addrlen=sizeof(address);
                
                printf("before accept\r\n");
                if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
                {
                    printf("accept failed\r\n");
                    close(sockfd);
                    return false;
                }
              
                printf("-------accept fd: %d\r\n",new_socket);
                
                //inform user of socket number - used in send and receive commands
                printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));                             
            }
            
            for(int i=0;i<max_clients;i++)
            {                                
                if(client_socket[i]>0)
                {
                    if(FD_ISSET(client_socket[i],&select_read_fds))
                    {
                        int client_socket_fd=client_socket[i];
                        
                        printf("before recv\r\n");
                        int numBytes = recv(client_socket_fd,buf,bufSize-1,0);
                        
                        if(numBytes<0)
                        {
                            printf("recv failed\r\n");
                            return false;
                        }
                        
                        if(numBytes==0)
                        {
                            close(client_socket_fd);
                            client_socket[i]=0;
                        }
                        else
                        {
                            buf[numBytes]=0;
                            
                            printf("[ %s ]\r\n",buf);
                            
                            
                            char response[bufSize];
                            
                            getResponse(buf,response);
                            
                            
                            if(send(client_socket_fd,response,strlen(response),0)!=(ssize_t)strlen(response))
                            {
                                printf("send failed\r\n");
                                return false;
                            }
                        }
                    }
                }
            }

            if(new_socket>0)
            {
                //add new socket to array of sockets
                for (int i = 0; i < max_clients; i++) 
                {
                    //if position is empty
                    if( client_socket[i] == 0 )
                    {
                        client_socket[i] = new_socket;                         
                        break;
                    }
                }
            }
        }
    }
}

