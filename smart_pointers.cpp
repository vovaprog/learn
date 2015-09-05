#include <memory>
#include <iostream>

using namespace std;
 
void f(weak_ptr<int> &gw)
{
    if (shared_ptr<int> spt = gw.lock()) { // необходимо скопировать в shared_ptr перед использованием
        std::cout << *spt << "\n";
    } else {
        std::cout << "gw is expired\n";
    }
}
 
void test_smart_pointers()
{
    weak_ptr<int> gw;
    
    {
        shared_ptr<int> sp = make_shared<int>(42);
        gw = sp;
 
        f(gw);
    }
 
    f(gw);
}

