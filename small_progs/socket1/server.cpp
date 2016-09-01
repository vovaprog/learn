#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

#include "message.h"
#include "util.h"

int sockfd = -1;


void sig_int_handler(int i)
{
    printf("sig int handler\n");

    if(sockfd > 0)
    {
        close(sockfd);
    }

    exit(-1);
}


void processRequest1(int sock)
{
    Message msg;

    int ret = readBytes(sock, (char*)&msg, sizeof(Message));
    if(ret != sizeof(Message))
    {
        close(sock);
        return;
    }
    msg.id = msg.id + 1;

    writeBytes(sock, (char*)&msg, sizeof(Message));
    close(sock);
}

void processRequest2(int sock)
{
    Message msg;    
    while(true)
    {
        int ret = readBytes(sock, (char*)&msg, sizeof(Message));
        if(ret != sizeof(Message))
        {
            close(sock);
            return;
        }
        msg.id = msg.id + 1;
    
        writeBytes(sock, (char*)&msg, sizeof(Message));
    }
}


bool initSocket()
{
    signal(SIGINT, sig_int_handler);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("socket failed\n");
        return false;
    }

    int enable = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
    {
        printf("setsockopt failed\n");
        close(sockfd);
        return false;
    }

    struct sockaddr_in serv_addr;
    /*, cli_addr;
    socklen_t clilen = sizeof(sockaddr_in);*/

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(7000);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in)) != 0)
    {
        printf("bind failed: %s\r\n", strerror(errno));
        close(sockfd);
        return false;
    }

    if(listen(sockfd, 1000) != 0) //length of queue of pending connections
    {
        printf("listen failed!\r\n");
        close(sockfd);
        return false;
    }
    
    return true;
}

bool server1()
{
    if(!initSocket())
    {
        return false;
    }

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(sockaddr_in);    
    
    while(true)
    {
        int clientSocket = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

        if(clientSocket < 0)
        {
            printf("accept failed\r\n");
        }
        else
        {
            processRequest1(clientSocket);
            //processRequest2(clientSocket);            
        }
    }
}

bool server2()
{
    if(!initSocket())
    {
        return false;
    }

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(sockaddr_in);    
    
    printf("q\n");
    while(true)
    {
        int clientSocket = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

        if(clientSocket < 0)
        {
            printf("accept failed\r\n");
        }
        else
        {
            printf("1\n");
            
            unsigned char buf[1000];
            
            while(true)
            {
                int curBytes = read(clientSocket, buf, 1000);

                for(int i=0;i<curBytes-1;++i)
                {
                    if(!(buf[i] == 255 && buf[i+1]==0 || buf[i] + 1 == buf[i+1]))
                    {
                        printf("invalid data\n");
                        return false;
                    }
                }
                
                if(writeBytes(clientSocket, (char*)buf, curBytes)!=curBytes)
                {
                    printf("writeBytes failed\n");
                    return false;
                }
            }
        }
    }
}

int main()
{
    //server1();
    server2();

    return 0;
}
