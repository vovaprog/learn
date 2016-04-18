#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);

void work1(int x, int y, int z, promise<int> result)
{
    result.set_value(x+y+z);
}

void test_future1()
{
    promise<int> myPromise1;
    future<int> myFuture1 = myPromise1.get_future();
    thread myThread1(work1,1,2,3,move(myPromise1));
    
    myFuture1.wait();
    int result = myFuture1.get();
    
    debug2("%d",result);
    
    myThread1.join();    
}

void work2(int x, int y, int z, promise<int> result)
{
    result.set_exception(make_exception_ptr(invalid_argument("works2!")));
}

void test_future2()
{    
    promise<int> myPromise1;
    future<int> myFuture1 = myPromise1.get_future();
    thread myThread1(work2,1,2,3,move(myPromise1));
    
    myFuture1.wait();

    try{
        int result = myFuture1.get();
        debug2("%d",result);
    }catch(invalid_argument ex){
        cout <<"catch in main thread: "<<ex.what()<<endl;
    }    

    myThread1.join();
}

int work3(int x, int y, int z)
{
    return x+y+z;
}

void test_packaged_task1()
{
    packaged_task<int()> pack_task(bind(work3,1,2,3));
    future<int> future1 = pack_task.get_future();
    pack_task();
    int result = future1.get();
    debug2("packaged task: %d",result);   
}

int main()
{
    test_future1();
    test_future2();
    test_packaged_task1();
    
    return 0;    
}