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
    
    /*Data(const Data &d)
    {
        cout <<"copy ctr Data(const Data &d) (d.x="<<d.x<<")\n";
        x = d.x;
    }*/
    
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

template<bool x> struct StaticAssertion;
template<> struct StaticAssertion<true> {};
#define PIRE_STATIC_ASSERT(x) \
enum { PireStaticAssertion ## __LINE__ = sizeof(StaticAssertion<(bool) (x)>) }


int main()
{    
    Data d(5);
    Data &rd = d;
    Data *pd = &rd;
 
    //PIRE_STATIC_ASSERT(std::is_copy_constructible<Data>::value);

    static_assert(std::is_copy_constructible<Data>::value, "Data is not copy constructible");

    return 0;
}


