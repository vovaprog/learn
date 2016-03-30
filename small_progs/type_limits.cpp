#include <iostream>
#include <limits>
#include <typeinfo>
#include <cxxabi.h>
#include <cstdlib>

using namespace std;

template<typename T>
std::string type_name()
{
    int status;
    std::string tname = typeid(T).name();
    char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
    if(status == 0) {
        tname = demangled_name;
        std::free(demangled_name);
    }   
    return tname;
}

//=================================================================================================

template <class T>
struct is_char_type { static const bool VALUE = false; };
template <> struct is_char_type<char> { static const bool VALUE = true; };
template <> struct is_char_type<signed char> { static const bool VALUE = true; };
template <> struct is_char_type<unsigned char> { static const bool VALUE = true; };
template <> struct is_char_type<wchar_t> { static const bool VALUE = true; };
template <> struct is_char_type<char16_t> { static const bool VALUE = true; };
template <> struct is_char_type<char32_t> { static const bool VALUE = true; };

//=================================================================================================
//using struct here, because function template partial specialization is not allowed in c++.

template<class T,bool is_char> struct printMinMax;

template<class T> struct printMinMax<T,false>
{
    static void print()
    {
        cout << "Minimum value 1: " << numeric_limits<T>::min() << endl;
        cout << "Maximum value 1: " << numeric_limits<T>::max() << endl;
    }
};

template<class T> struct printMinMax<T,true>
{
    static void print()
    {
        cout << "Minimum value 2: " << (long long int)numeric_limits<T>::min() << endl;
        cout << "Maximum value 2: " << (long long int)numeric_limits<T>::max() << endl;            
    }
};

//=================================================================================================

template<class T>
void printLimits()
{
    cout <<"type: "<<type_name<T>()<<endl;
    cout << boolalpha;
    cout <<"sizeof: "<<sizeof(T)<<endl;
    
    printMinMax<T,is_char_type<T>::VALUE>::print();
    
    cout << "is signed: " << numeric_limits<T>::is_signed << endl;
    cout << "Non-sign bits: " << numeric_limits<T>::digits << endl;
    cout << "has infinity: " << numeric_limits<T>::has_infinity << endl;
    cout <<endl;
}


int main () 
{  
    printLimits<int>();
    printLimits<unsigned int>();
    
    printLimits<char>();
    printLimits<signed char>();    
    printLimits<unsigned char>();
    printLimits<wchar_t>();
    printLimits<char16_t>();
    printLimits<char32_t>();    
    
    printLimits<float>();
    printLimits<double>();
    
    return 0;
}

