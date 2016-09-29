#include "../SimpleProfiler.h"
#include "../tools/Spinlock.h"

#include <queue>
#include <boost/lockfree/spsc_queue.hpp>

using namespace std;

int main()
{
	mutex mtx;
	long long int accum = 0;

	{
		boost::lockfree::spsc_queue<int> q(10000000); 
	
		{
			SimpleProfiler prof("spsc_queue");
			
			for(int i=0;i<10000000;++i)
			{				
				//lock_guard<mutex> lock(mtx);
				q.push(i);
			}
		
			for(int i=0;i<10000000;++i)
			{
				int x;
				q.pop(x);
				accum += x;
			}
		}
	}
	
	{
		queue<int> q;
		
		{
			SimpleProfiler prof("queue");
			
			for(int i=0;i<10000000;++i)
			{
				//lock_guard<mutex> lock(mtx);
				q.push(i);
			}
		
			for(int i=0;i<10000000;++i)
			{
				int x = q.front();
				accum += x;
				q.pop();
			}
		}
	}

	
	{
		boost::lockfree::spsc_queue<int> q(100); 
	
		{
			SimpleProfiler prof("spsc_queue 50");
			
			for(int k=0;k<1000000;++k)
			{
				for(int i=0;i<50;++i)
				{				
					//lock_guard<mutex> lock(mtx);
					q.push(i);
				}
			
				for(int i=0;i<50;++i)
				{
					int x;
					q.pop(x);
					accum += x;
				}
			}
		}
	}

	{
		queue<int> q;
	
		{
			SimpleProfiler prof("queue 50");
			
			for(int k=0;k<1000000;++k)
			{
				for(int i=0;i<50;++i)
				{				
					//lock_guard<mutex> lock(mtx);
					q.push(i);
				}
			
				for(int i=0;i<50;++i)
				{
					int x = q.front();
					accum += x;
					q.pop();					
				}
			}
		}
	}
	
	{
		SimpleProfiler prof("mutex");
		
		for(int i=0;i<10000000;++i)
		{
			{
				lock_guard<mutex> lock(mtx);			
				++accum;
			}
		}		
	}

	Spinlock spin;
	{		
		SimpleProfiler prof("spinlock");
		
		for(int i=0;i<10000000;++i)
		{
			{
				lock_guard<Spinlock> lock(spin);			
				++accum;
			}
		}		
	}
	
		
	cout <<endl<< accum <<endl;
	
	
	return 0;	
}
