#include <queue>
#include <iostream>
#include <memory>

using namespace std;

#include "spaceship.h"

template<class T>
void printQueue(T &q)
{
    cout <<"---------------------"<<endl;
    while(!q.empty())
    {
        cout <<"[[["<<q.top()<<"]]]"<<" ";        
        q.pop();
    }
    cout <<endl;
    cout <<"---------------------"<<endl;
}

template<class T>
void printQueue3(T &q)
{
    cout <<"---------------------"<<endl;
    while(!q.empty())
    {
        cout <<"[[["<<*q.top()<<"]]]"<<" ";        
        q.pop();
    }
    cout <<endl;
    cout <<"---------------------"<<endl;
}

void learnPriorityQueue1()
{
    priority_queue<int> q;
    
    vector<int> data{3,7,2,2,6,7,2,7,2,3,4,2,8,9};
    
    for(auto v : data)
    {
        q.push(v);
    }
    
    printQueue(q);
    
    
    priority_queue<int,vector<int>,greater<int>> q2;
    
    for(auto v : data)
    {
        q2.push(v);
    }
    
    printQueue(q2);    
}

void learnPriorityQueue2()
{
    priority_queue<Spaceship> q;
    
    q.push(Spaceship("mars one",3));        
    q.push(Spaceship("juno",5));
    q.push(Spaceship("cassini",1));
    
    
    printQueue(q);    
}

template<class T>
bool compareTemplateFunction(T &s0,T &s1)
{
    return (*s0).weight > (*s1).weight;
}

bool compareFunction(unique_ptr<Spaceship> &s0,unique_ptr<Spaceship> &s1)
{
    return (*s0).weight < (*s1).weight;
}

void learnPriorityQueue3()
{
    {
        //compare lambda
        auto comp = []( unique_ptr<Spaceship> &s0, unique_ptr<Spaceship> &s1 ) { return (*s0).weight > (*s1).weight; };    
        priority_queue<unique_ptr<Spaceship>,vector<unique_ptr<Spaceship>>,decltype(comp)> q(comp);

        q.push(unique_ptr<Spaceship>(new Spaceship("mars one",3)));
        q.push(unique_ptr<Spaceship>(new Spaceship("juno",5)));
        q.push(unique_ptr<Spaceship>(new Spaceship("cassini",1)));
        
        printQueue3(q);
    }

    {
        //compare template function
        priority_queue<unique_ptr<Spaceship>,vector<unique_ptr<Spaceship>>,function<bool(unique_ptr<Spaceship>&,unique_ptr<Spaceship>&)>> q(compareTemplateFunction<unique_ptr<Spaceship>>);
        
        q.push(unique_ptr<Spaceship>(new Spaceship("mars one",3)));
        q.push(unique_ptr<Spaceship>(new Spaceship("juno",5)));
        q.push(unique_ptr<Spaceship>(new Spaceship("cassini",1)));
        
        printQueue3(q);
    }
        
    {
        //compare function
        priority_queue<unique_ptr<Spaceship>,vector<unique_ptr<Spaceship>>,function<bool(unique_ptr<Spaceship>&,unique_ptr<Spaceship>&)>> q(compareFunction);

        q.push(unique_ptr<Spaceship>(new Spaceship("mars one",3)));
        q.push(unique_ptr<Spaceship>(new Spaceship("juno",5)));
        q.push(unique_ptr<Spaceship>(new Spaceship("cassini",1)));
        
        printQueue3(q);
    }
}

void learnPriorityQueue()
{
    //learnPriorityQueue1();
    //learnPriorityQueue2();
    learnPriorityQueue3();
}


