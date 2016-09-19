#include <iostream>

using namespace std;

struct Data
{
    long long int x;
    long long int y;
    long long int z;
};

inline long long int getMilliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch()
           ).count();
}


int main()
{
    const int BUF_SIZE = 1000000;
    Data *ds = new Data[BUF_SIZE];

    for(int i = 0; i < BUF_SIZE; ++i)
    {
        ds[i].x = rand();
        ds[i].y = rand();
        ds[i].z = rand();
    }



    int eqCounter = 0;

    long long int millisStart = getMilliseconds();

    for(int i = 0; i < 5000; ++i)
    {
        for(int i = 0; i < BUF_SIZE; ++i)
        {
            if(ds[i].x == ds[i].y)
                ++eqCounter;
        }
    }

    cout << "index loop: " << (getMilliseconds() - millisStart) << endl;

    millisStart = getMilliseconds();

    for(int i = 0; i < 5000; ++i)
    {
        Data *end = ds + BUF_SIZE;
        for(Data *p = ds; p != end; ++p)
        {
            if(p->x == p->y)
                ++eqCounter;
        }
    }

    cout << "pointer loop: " << (getMilliseconds() - millisStart) << endl;

    cout << eqCounter << endl;

    return 0;
}
