#include <bits/stdc++.h>

#include <unistd.h>
#include <sys/time.h>

using namespace std;

/*
core i7 930:
sizeof DataPacked: 9
sizeof Data: 16
sizeof buf packed: 90000000
sizeof buf: 160000000
pack count:10000000, repeat:100        : 1129
aligned count:10000000, repeat:100     : 1985
pack count:100, repeat:10000000        : 721
aligned count:100, repeat:10000000     : 894

core 2 quad q9550:
sizeof DataPacked: 9
sizeof Data: 16
sizeof buf packed: 90000000
sizeof buf: 160000000
pack count:10000000, repeat:100        : 3443
aligned count:10000000, repeat:100     : 6033
pack count:100, repeat:10000000        : 1127
aligned count:100, repeat:10000000     : 945
*/

class SimpleProfiler
{
public:
    SimpleProfiler(const std::string &name): name(name)
    {
        startMillis = getMilliseconds();
    }

    ~SimpleProfiler()
    {
        std::cout << name << ": " << getMilliseconds() - startMillis << std::endl;
    }

    long long int getMilliseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return (long long int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    }

private:
    long long int startMillis;
    std::string name;
};

//================================================================================================
//================================================================================================
//================================================================================================



#pragma pack(push, 1)
struct DataPacked
{
    char a[1];
    long long int x;
};
#pragma pack(pop)

struct Data
{
    char a[1];
    long long int x;
};



const int BUF_SIZE = 10000000;

DataPacked bufPack[BUF_SIZE];
Data buf[BUF_SIZE];



template<class T>
void writeBuf(T *buf, int length, int repeat)
{
    for (int r = 0; r < repeat; ++r)
    {
        for (int i = 0; i < length; ++i)
        {
            buf[i].x = i;
        }
    }
}




int main()
{
    cout << "sizeof DataPacked: " << sizeof(DataPacked) << endl;
    cout << "sizeof Data: " << sizeof (Data) << endl;
    cout << "sizeof buf packed: " << sizeof(bufPack) << endl;
    cout << "sizeof buf: " << sizeof (buf) << endl;

    {
        SimpleProfiler prof("pack count:10000000, repeat:100        ");
        writeBuf(bufPack, BUF_SIZE, 100);
    }

    {
        SimpleProfiler prof("aligned count:10000000, repeat:100     ");
        writeBuf(buf, BUF_SIZE, 100);
    }

    {
        SimpleProfiler prof("pack count:100, repeat:10000000        ");
        writeBuf(bufPack, 100, 10000000);
    }

    {
        SimpleProfiler prof("aligned count:100, repeat:10000000     ");
        writeBuf(buf, 100, 10000000);
    }

    return 0;
}


