#include <iostream>
#include <boost/lockfree/spsc_queue.hpp>

using namespace std;

int main()
{
    //boost::lockfree::spsc_queue<int> q(3);
    boost::lockfree::spsc_queue<int, boost::lockfree::capacity<3> > q;

    int x;

    cout << q.push(1) << endl;
    cout << q.push(2) << endl;
    cout << q.push(3) << endl;
    cout << q.push(4) << endl;
    cout << q.push(5) << endl;
    cout << q.pop(x) << endl;
    cout << q.pop(x) << endl;
    cout << q.push(6) << endl;
    cout << q.push(7) << endl;
    cout << q.push(8) << endl;

    cout <<"------"<<endl;

    cout << q.pop(x); cout << " " << x<<  endl;
    cout << q.pop(x); cout << " " << x<<  endl;
    cout << q.pop(x); cout << " " << x<<  endl;
    cout << q.pop(x); cout << " " << x<<  endl;
    cout << q.pop(x); cout << " " << x<<  endl;

    return 0;
}


