/*#include <iostream>
#include <functional>

#include <boost/signals2.hpp>*/

#include <learn_signals_include.h>


using namespace std;
using namespace boost::signals2;

/*void setHandlers()
{
    signal(SIGHUP, sig_handler);
    signal(SIGQUIT, sig_handler);
    signal(SIGILL, sig_handler);
    signal(SIGTRAP, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGIOT, sig_handler);
    signal(SIGBUS, sig_handler);
    signal(SIGFPE, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGSEGV, sig_handler);
    signal(SIGUSR2, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGALRM, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGSTKFLT, sig_handler);
    signal(SIGCLD, sig_handler);
    signal(SIGCHLD, sig_handler);
    signal(SIGCONT, sig_handler);
    signal(SIGSTOP, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGTTIN, sig_handler);
    signal(SIGTTOU, sig_handler);
    signal(SIGURG, sig_handler);
    signal(SIGXCPU, sig_handler);
    signal(SIGXFSZ, sig_handler);
    signal(SIGVTALRM, sig_handler);
    signal(SIGPROF, sig_handler);
    signal(SIGWINCH, sig_handler);
    signal(SIGPOLL, sig_handler);
    signal(SIGPWR, sig_handler);
    signal(SIGSYS, sig_handler);
    signal(SIGUNUSED, sig_handler);
}*/


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

