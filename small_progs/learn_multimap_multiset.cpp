#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);

typedef long long int int64;

void printByKey(multimap<string,string> &mm, string &key)
{
	cout <<"<<---------------------"<<endl;
    
    auto p = mm.equal_range(key);
    
    for(auto it=p.first;it!=p.second;++it)
    {
    	cout <<it->second<<endl;	
    }
    
    cout <<"--------------------->>"<<endl;	
}

int main()
{
    multimap<string,string> mm;
    
    //================= insert items =================================
    
    mm.insert(make_pair("key1","val11"));
    mm.emplace("key1","val12_qqq");
    //mm.insert(make_pair("key1","val12"));    
    mm.insert(make_pair("key2","val21"));
    mm.insert(make_pair("key2","val22"));
    mm.insert(make_pair("key3","val31"));
    mm.insert(make_pair("key1","val13"));
    
    //================= insert items =================================
    
    
    //================= iterate map ==================================
    
    for(auto &p : mm)
    {
    	cout <<p.first<<" "<<p.second<<endl;	    	
    }
    cout <<"---\n"<<mm.begin()->first<<endl;    
    
    //================= iterate map ==================================
    
    
    string key = "key2";
    
    //=================== get values by key =======================
    
    cout <<"---------------------"<<endl;
    
    auto it = mm.find(key);    
    while(it->first==key)
    {
    	cout <<it->second<<endl;
    	++it;
    }
    
    cout <<"---------------------"<<endl;
    
    //=================== get values by key =======================
    
    
    //=================== get values by key =======================
    
    cout <<"---------------------"<<endl;
    
    auto p = mm.equal_range(key);
    
    for(auto it=p.first;it!=p.second;++it)
    {
    	cout <<it->second<<endl;	
    }
    
    cout <<"---------------------"<<endl;
    
    //=================== get values by key =======================
    
    //===================== erase elements ========================
    
    cout <<"erase test\n";
    
    printByKey(mm,key);
    //int removedCount = mm.erase(key); //Return value Number of elements removed.
    auto p2 = mm.equal_range(key);
    cout <<"number of items: "<<distance(p2.first,p2.second)<<endl;
    mm.erase(p2.first,p2.second); //Return value  Iterator following the last removed element. 
    printByKey(mm,key);
    
    //===================== erase elements ========================
    
    //cout <<"removed count: "<<removedCount<<endl;
    
    
    //=================== priority queue ==========================    
    priority_queue<string> q;
    q.push("hello");
    q.emplace("world");
    q.push("program");
    cout <<q.top()<<" "<<q.top()<<q.size()<<endl;
    q.pop();
    cout <<q.top()<<" "<<q.top()<<q.size()<<endl;    
    //=================== priority queue ==========================
    
    return 0;
}
