#include <iostream>
#include <vector>
#include <boost/intrusive/list.hpp>

using namespace std;

struct Data1: public boost::intrusive::list_base_hook<> {
    int a, b, c, d;
};

int main()
{
    cout << "hello, world!" << endl;

    vector<Data1> v;
    v.reserve(100);

    boost::intrusive::list<Data1> lst;

    for(int i=0;i<100;++i)
    {
        Data1 d;
        d.a = i;
        v.push_back(d);
        lst.push_back(v[i]);
    }

    for(auto &d : lst)
    {
        cout << d.a << endl;
    }

    return 0;
}


