#include <iostream>
#include <climits>

using namespace std;

void test1()
{
    long long int x = (long long int)INT_MAX * 20;

    if(x > INT_MAX)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
}

void test2()
{
    cout << "sizeof(pthread_t): " << sizeof(pthread_t) << endl;
}

int main()
{
    //test1();
    test2();

    return 0;
}

