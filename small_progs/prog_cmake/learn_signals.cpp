#include <unistd.h>
#include <iostream>
#include <string.h>
#include <thread>
#include <signal.h>

using namespace std;




void learn_signals_thread(int threadNumber)
{


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




		close(read_fd);

		char buf[1000];
		strcpy(buf, "works!");

		while(true)
		{
			sighandler_t r = signal(SIGPIPE, SIG_IGN);
			cout <<"parent r:"<< (long long int)r << endl;

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



