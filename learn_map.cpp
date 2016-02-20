#include <bits/stdc++.h>

#include "SimpleProfiler.h"

using namespace std;

class User{
public:   
    string name;
    
    User(){}
    User(const char* name):name(name){}
    
};

/*inline bool tryGetValue(map<string,User> &m, string &key, User &u)
{
    auto it = m.find(key);
    if(it!=m.end())
    {
        u = it->second;
        return true;
    }
    return false;
}*/

template<class TMap,class TKey,class TValue>
inline bool tryGetValue(TMap &m, TKey &key, TValue &u)
{
    auto it = m.find(key);
    if(it!=m.end())
    {
        u = it->second;
        return true;
    }
    return false;
}


/*template<class TKey,class TValue>
inline bool tryGetValue(unordered_map<TKey,TValue> &m, TKey &key, TValue &u)
{
    auto it = m.find(key);
    if(it!=m.end())
    {
        u = it->second;
        return true;
    }
    return false;
}*/

void learn_map()
{
    map<string, User> usersIndex;
    map<string, User> usersEmplace;
    map<string, User> usersInsert;
    vector<string> keys;

    for(int i=0;i<1000000;i++)
    {
        keys.push_back(to_string(i));  
    }    
    

    {
        SimpleProfiler sp("map emplace");
        for(auto& key : keys)
        {        
            usersEmplace.emplace(key, "abc");
        }
    }

    {
        SimpleProfiler sp("map[]");
        for(auto& key : keys)
        {        
            usersIndex[key] = User("abc");
        }
    }
    
    {
        SimpleProfiler sp("map insert");
        for(auto& key : keys)
        {        
            usersInsert.insert(pair<string,User>(key, User("abc")));
        }
    }
    
    {
        SimpleProfiler sp("map find");
        for(auto& key : keys)
        {
            auto it = usersIndex.find(key);
            if(it!=usersIndex.end())
            {
                User& u = it->second;
                string s = u.name;
            }        
        }
    }

    {
        SimpleProfiler sp("map get []");
        for(auto& key : keys)
        { 
            User &u = usersIndex[key];
            string s = u.name;
        }
    }

    {
        SimpleProfiler sp("map count []");
        for(auto& key : keys)
        {
            if(usersIndex.count(key)>0)
            {
                string s = usersIndex[key].name;
            }
        }
    }

    {
        SimpleProfiler sp("map tryGetValue");
        for(auto& key : keys)
        {
            User u;
            if(tryGetValue(usersIndex,key,u))
            {
                string s = u.name;
            }
        }
    }
    
    /*
    //iterate through map
    for(auto& p : users)
    {
        cout << p.first << "   " << p.second.name<<endl;
    }*/
}


void learn_unordered_map()
{
    unordered_map<string, User> usersIndex;
    unordered_map<string, User> usersEmplace;
    unordered_map<string, User> usersInsert;
    vector<string> keys;

    for(int i=0;i<1000000;i++)
    {
        keys.push_back(to_string(i));  
    }    
    

    {
        SimpleProfiler sp("map emplace");
        for(auto& key : keys)
        {        
            usersEmplace.emplace(key, "abc");
        }
    }

    {
        SimpleProfiler sp("map[]");
        for(auto& key : keys)
        {        
            usersIndex[key] = User("abc");
        }
    }
    
    {
        SimpleProfiler sp("map insert");
        for(auto& key : keys)
        {        
            usersInsert.insert(pair<string,User>(key, User("abc")));
        }
    }
    
    {
        SimpleProfiler sp("map find");
        for(auto& key : keys)
        {
            auto it = usersIndex.find(key);
            if(it!=usersIndex.end())
            {
                User& u = it->second;
                string s = u.name;
            }        
        }
    }

    {
        SimpleProfiler sp("map get []");
        for(auto& key : keys)
        {
            string s = usersIndex[key].name;
        }
    }

    {
        SimpleProfiler sp("map count []");
        for(auto& key : keys)
        {
            if(usersIndex.count(key)>0)
            {
                string s = usersIndex[key].name;
            }
        }
    }

    {
        SimpleProfiler sp("map tryGetValue");
        for(auto& key : keys)
        {
            User u;
            if(tryGetValue(usersIndex,key,u))
            {
                string s = u.name;
            }
        }
    }
    
    /*
    //iterate through map
    for(auto& p : users)
    {
        cout << p.first << "   " << p.second.name<<endl;
    }*/
}





