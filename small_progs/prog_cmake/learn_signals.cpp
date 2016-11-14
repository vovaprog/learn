#include <unistd.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <signal.h>
#include <unistd.h>

using namespace std;

void sigIntHandler(int signalNumber)
{
	long long int tid = pthread_self();
	long long int pid = getpid();

	cout <<"sig int pid: " << pid << "   tid: "<<tid << endl;
	exit(0);
}


void learn_signals_thread(int threadNumber)
{
	cout <<"tnumber: "<<threadNumber<<endl;

	if(threadNumber == 1)
	{
		cout <<"blocking[[["<<threadNumber<<"]]]"<<endl;
		//signal(SIGPIPE, SIG_IGN);

		struct sigaction sa;
		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;

		if(sigaction(SIGPIPE, &sa, NULL) != 0)
		{
			perror("sigaction failed\n");
		}

	}


	int pipe_fds[2],read_fd,write_fd;

	if(pipe(pipe_fds)!=0)
	{
		cout << "pipe failed!"<<endl;
	}

	read_fd=pipe_fds[0];
	write_fd=pipe_fds[1];

	pid_t result=fork();

	if(result==0)
	{
		cout <<"child"<<endl;

		close(write_fd);



		char buf[1001];

		strcpy(buf,"works!");

		for(int i=0;i<3;++i)
		{
			read(read_fd, buf, 1000);

			sleep(1);
		}
	}
	else if(result>0)
	{
        sleep(1);

    	struct sigaction sa;
    	memset(&sa, 0, sizeof(struct sigaction));
    	sa.sa_handler = sigIntHandler;
    	sa.sa_flags = 0;


     	if(sigaction(SIGINT, &sa, NULL) != 0)
    	{
	    	perror("sigaction failed\n");
    	}        
        

		close(read_fd);

		char buf[1000];
		strcpy(buf, "works!");

		while(true)
		{			
			cout <<"writing th:"<<threadNumber<<endl;
			if(write(write_fd, buf, strlen(buf))<0)
			{
				printf("write error\n");
				return;
			}

			sleep(1);
		}
	}
	else
	{
		cout <<"error!"<<endl;
	}


}


void learn_signals()
{
/*	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigIntHandler;
	sa.sa_flags = 0;

 	if(sigaction(SIGINT, &sa, NULL) != 0)
	{
		perror("sigaction failed\n");
	} 
*/


	const int numThreads = 3;
	thread *threads[numThreads];

	for(int i=0;i<numThreads;++i)
	{
		threads[i] = new thread(learn_signals_thread, i);
	}

	for(int i=0;i<numThreads;++i)
	{
		threads[i]->join();
	}
}



