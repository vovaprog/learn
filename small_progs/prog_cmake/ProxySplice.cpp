#include <TransferRingBuffer.h>

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
#include <climits>

int socketListen(int port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)
	{
		printf("socket failed\n");
		return -1;
	}

	int enable = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
	{
		printf("setsockopt failed\n");
		close(sockfd);
		return -1;
	}

	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0, sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in)) != 0)
	{
		printf("bind failed: %s\r\n", strerror(errno));
		close(sockfd);
		return -1;
	}

	if(listen(sockfd, 1000) != 0) //length of queue of pending connections
	{
		printf("listen failed\r\n");
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int socketConnect(const char *address, int port)
{
	struct sockaddr_in remoteaddr;
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr.s_addr = inet_addr(address);
	remoteaddr.sin_port = htons(port);

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		printf("socket failed!\r\n");
		return -1;
	}

	if(connect(sock, (struct sockaddr*)&remoteaddr, sizeof(remoteaddr)) != 0)
	{
		printf("connect failed!\r\n");
		close(sock);
		return -1;
	}

	return sock;
}



int proxySplice()
{
	int serverFd = socketListen(7000);
	int connectFd = socketConnect("127.0.0.1", 7001);

	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(sockaddr_in);
	int clientFd = accept(serverFd, (struct sockaddr*) &cli_addr, &clilen);


	int pipefd[2];

	if(pipe(pipefd) != 0)
	{
		perror("pipe failed");
		return -1;
	}


	while(true)
	{
		int nr = splice(clientFd, NULL, pipefd[1], NULL, 100000, 0);
		if(nr <= 0)
		{
			perror("splice failed");
			break;
		}
		do
		{
			int ret = splice(pipefd[0], NULL, connectFd, NULL, nr, 0);
			if (ret <= 0)
			{
				perror("splice failed");
				break;
			}

			nr -= ret;
		} while (nr);
	}
	close(pipefd[0]);
	close(pipefd[1]);

	return 0;
}


int proxyCopy()
{
	int serverFd = socketListen(7000);
	int connectFd = socketConnect("127.0.0.1", 7001);

	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(sockaddr_in);
	int clientFd = accept(serverFd, (struct sockaddr*) &cli_addr, &clilen);

	TransferRingBuffer buffer;
	buffer.init(100000);

	long long int sumRead = 0;
	int counter = 0;

	while(true)
	{
		void *data;
		int size;
		int bytes;

		if(buffer.startWrite(data, size))
		{
			bytes = read(clientFd, data, size);

			if(bytes <= 0)
			{
				printf("read <= 0\n");
				return -1;
			}

			buffer.endWrite(bytes);

			sumRead += bytes;
			++counter;

			if(counter>=10000)
			{
				printf("avg read: %lld\n", sumRead/counter);fflush(stdout);
				counter = 0;
				sumRead = 0;
			}
		}
		else
		{
			printf("startWrite failed\n");
			return -1;
		}

		if(buffer.startRead(data, size))
		{
			bytes = write(connectFd, data, size);

			if(bytes <= 0)
			{
				printf("write <= 0\n");
				return -1;
			}

			buffer.endRead(bytes);
		}
		else
		{
			printf("startRead failed\n");
			return -1;
		}
	}

	return 0;
}

