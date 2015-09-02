#include <iostream>
#include <functional>

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
    std::cout << x << " * " << y << " = " << x*y << std::endl;    
}

void divFunction(double x, double y)
{
    std::cout << "div="<< x/y << std::endl;    
}


void learn_signals1()
{ 
  signal<void ()> sig;

  HelloWorld hello;
  sig.connect(hello);
  sig.connect(&testFunction);


  sig();
}

void learn_signals2()
{ 
  signal<void (double,double)> sig;

  SumStruct ss;
  sig.connect(ss);
  sig.connect(&divFunction);
  {  
      scoped_connection scoped_con (sig.connect(&mulFunction));
      sig(3.0, 4.0);
  }
  cout <<"--------------"<<endl;
  
  sig(3.0, 4.0);
}

void learn_signals3()
{ 
    auto f = bind(mulFunction,5,6);
    f();
    
    auto f2=bind(mulFunction,_2,_1);
    f2(1,5);
}

void learn_signals()
{
    //learn_signals1();
    //learn_signals2();
    learn_signals3();
}

