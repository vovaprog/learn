#include <array>
#include <forward_list>
#include <iostream>
#include <algorithm>

using namespace std;

void learnArrayContainer()
{
    {
        array<int,5> list{5,3,6,2,6};
               
        for(auto &x : list)
        {
            cout <<x<<endl;
        }    
        
        sort(list.begin(),list.end());
        
        cout <<"--------------"<<endl;
        
        for(auto &x : list)
        {
            cout <<x<<endl;
        }
        
        sort(list.begin(),list.end(),[](int a,int b)->bool{ return a > b;});
        
        cout <<"--------------"<<endl;
        
        for(auto &x : list)
        {
            cout <<x<<endl;
        }    
    }
    
    
    {
        cout <<"========== forward list =========="<<endl;
        
        forward_list<int> list{5,3,6,2,6};
        
        for(auto &x : list)
        {
            cout <<x<<endl;
        }    
        
        list.sort(); //list.begin(),list.end(),[](int a,int b)->bool{ return a > b;});
    
        cout <<"--------------"<<endl;
        
        for(auto &x : list)
        {
            cout <<x<<endl;
        }
        
        list.sort([](int a,int b)->bool{ return a > b;});
    
        cout <<"--------------"<<endl;
        
        for(auto &x : list)
        {
            cout <<x<<endl;
        }        
    }
}
