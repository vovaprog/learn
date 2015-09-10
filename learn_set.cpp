#include <iostream>
#include <memory>
#include <set>

#include "spaceship.h"

using namespace std;

void learnSet1()
{
    set<Spaceship> st;
    
    st.insert(Spaceship("dawn",7.0));
    st.insert(Spaceship("rosetta",5.0));
    st.insert(Spaceship("new horizons",5.1));
    
    for(auto& s : st)
    {
        cout <<"----------"<<s<<endl;
    }
}

void learnSet2()
{
    auto compareFunction = [](const unique_ptr<Spaceship> &s0,const unique_ptr<Spaceship> &s1 )->bool { return (*s0).weight < (*s1).weight; };
    
    set<unique_ptr<Spaceship>,decltype(compareFunction)> st(compareFunction);
    
    st.insert(unique_ptr<Spaceship>(new Spaceship("dawn",7.0)));
    st.insert(unique_ptr<Spaceship>(new Spaceship("rosetta",3.0)));
    st.insert(unique_ptr<Spaceship>(new Spaceship("new horizons",9.0)));
    st.insert(unique_ptr<Spaceship>(new Spaceship("maven",9.0)));
    
    for(auto& s : st)
    {
        cout <<"----------"<<*s<<endl;
    }
}


void learnSet()
{
    //learnSet1();
    learnSet2();
}
