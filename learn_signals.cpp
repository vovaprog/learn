#include <iostream>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost::signals2;

struct HelloWorld 
{
  void operator()() const 
  { 
    std::cout << "Hello, World!" << std::endl;
  } 
};

void testFunction()
{
    cout <<"in testFunction"<<endl;
}

struct SumStruct 
{
  void operator()(double x, double y) const 
  { 
    std::cout << "sum="<< x+y << std::endl;
  } 
};

void mulFunction(double x, double y)
{
    std::cout << "mul="<< x*y << std::endl;    
}


void learn_signals1()
{ 
  signal<void ()> sig;

  HelloWorld hello;
  sig.connect(hello);
  sig.connect(testFunction);


  sig();
}

void learn_signals2()
{ 
  signal<void (double,double)> sig;

  SumStruct ss;
  sig.connect(ss);
  sig.connect(mulFunction);

  sig(3.0, 4.0);
}


void learn_signals()
{
    learn_signals1();
    learn_signals2();
}

