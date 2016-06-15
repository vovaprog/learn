#include <bits/stdc++.h>

using namespace std;

#define debug(args...) printf(args);
#define debug2(fmt,args...) printf(fmt,args);printf("   (%s)\n",#args);

//=====================================================================
#define debug3(args...) { vector<string> v = splitArgNames(#args); debugPrint(v.begin(), args); }
vector<string> splitArgNames(const string& s) 
{ vector<string> v; stringstream ss(s); for (string x; getline(ss, x, ',');) { v.emplace_back(x); } return move(v); }
void debugPrint(vector<string>::iterator it) { cout <<"\n"; }
template<typename T, typename... Args>
void debugPrint(vector<string>::iterator it, T head, Args... args) 
{ cout << *it <<" = "<< head << "     "; debugPrint(++it, args...); }
//=====================================================================

typedef long long int int64;

class Data{
public:    
    Data(){cout <<"Data()\n";}
    
    ~Data(){cout <<"~Data("<<x<<")\n";}
    
    Data(const Data &d)
    {
        cout <<"copy ctr Data(const Data &d) (d.x="<<d.x<<")\n";
        x = d.x;
    }
    
    //Data(Data &&d) = default;
    
    Data(Data &&d) noexcept :x(d.x) 
    {
        cout <<"move ctr Data(Data &&d) (d.x="<<d.x<<")\n";
    }

    Data(int i):x(i)
    {
        cout <<"Data(int "<<i<<")\n";
    }
    
    Data& operator=(const Data& a)
    {
        cout <<"operator= ("<<x<<","<<a.x<<")\n";
        x = a.x;
        return *this;
    }
    
    bool operator==(const Data &d) const
    {
        cout <<"operator==\n";
        return x == d.x;
    }

    int x;
    
    friend std::ostream& operator<<(std::ostream &os, const Data &d);
};

std::ostream& operator<<(std::ostream &os, const Data &d) { 
    return os << d.x << endl;
}

void testInt()
{
    vector<int> v;
    
    for(int i=0;i<33;++i)
    {
        v.push_back(i);
    }

    for(auto x : v)
    {
        debug3(x);
    }
    
    v.erase(remove(v.begin(), v.end(), 10), v.end());

    debug3("==========");
    
    for(auto x : v)
    {
        debug3(x);
    }
    
    debug3("==========");
    
    v.erase(remove_if(v.begin(), v.end(),[](int x)
        {
            return x % 2 == 0;            
        }),
        v.end());

    for(auto x : v)
    {
        debug3(x);
    }    
}

void testData()
{
    vector<Data> v;
    
    //v.reserve(5);
    
    for(int i=0;i<10;++i)
    {
        v.emplace_back(i);
    }
    
    for(auto& d : v)
    {
        cout << d;
        //debug3(d);
    }
    
    cout <<"===============\n";
    
    v.erase(remove(v.begin(), v.end(), Data(5)), v.end());
        
    cout <<"===============\n";
    
    int mod = 3;
    
    auto afterRemove = remove_if(v.begin(), v.end(), [mod](Data &d)
        {
            return d.x % mod == 0;
        });
    
    v.erase(afterRemove, v.end());
    
    for(auto& d : v)
    {
        cout << d;
    }        
}

int main()
{
    testData();
    
    cout <<"$$$\n";
    
    Data d(5);
    Data &rd = d;
    Data *pd = &rd;
    
    return 0;
}


