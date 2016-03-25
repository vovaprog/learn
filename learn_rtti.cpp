#include <iostream>    // cout
#include <typeinfo>    // for 'typeid'
#include <typeindex>

using namespace std;

class Person {
public:
   virtual ~Person() {}
};

class Employee : public Person {
};

class NoVirt
{
public:    
    int x;
};

int learn_rtti() 
{
   Person person;
   Employee employee;
   Person* ptr = &employee;
   Person& ref = employee;
   // The string returned by typeid::name is implementation-defined
   std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)
   std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)
   std::cout << typeid(ptr).name() << std::endl;      // Person* (statically known at compile-time)
   std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time
                                                      //           because it is the dereference of a
                                                      //           pointer to a polymorphic class)
   std::cout << typeid(ref).name() << std::endl;      // Employee (references can also be polymorphic)

   Person* p = nullptr;
   try {
      typeid(*p); // not undefined behavior; throws std::bad_typeid
   }
   catch (...) {
       cout <<"catch ..."<<endl;
   }

   //Person& pRef = *p; // Undefined behavior: dereferencing null
   //cout <<typeid(pRef).name()<<endl;      // does not meet requirements to throw std::bad_typeid
                      // because the expression for typeid is not the result
                      // of applying the unary * operator
                      
    NoVirt nv;
    cout <<typeid(nv).name()<<endl;
    
    int intVal=33;
    cout <<typeid(intVal).name()<<endl;
    
    float floatVal=33.3;
    cout <<typeid(floatVal).name()<<endl;
    
    
    std::cout << std::type_index(typeid(employee)).name() <<" "<<std::type_index(typeid(employee)).hash_code()<<" "
        << typeid(employee).hash_code() <<std::endl;
    cout <<"size_t: "<<sizeof(size_t)<<endl;
    
}