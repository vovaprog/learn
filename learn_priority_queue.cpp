#include <queue>
#include <iostream>

using namespace std;

#include "spaceship.h"

template<class T>
void printQueue(T &q)
{
    cout <<"---------------------"<<endl;
    while(!q.empty())
    {
        Spaceship ss=q.top();
        cout <<"[[["<<ss<<"]]]"<<" ";        
        q.pop();
    }
    cout <<endl;
    cout <<"---------------------"<<endl;
}

/*void learnPriorityQueue1()
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
}*/

void learnPriorityQueue2()
{
    priority_queue<Spaceship> q;
    
    q.push(Spaceship("mars one",3));        
    q.push(Spaceship("juno",5));
    q.push(Spaceship("cassini",1));
    
    
    printQueue(q);    
}

void learnPriorityQueue()
{
    //learnPriorityQueue1();
    learnPriorityQueue2();
}
