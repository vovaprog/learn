#include <iostream>
#include <typeinfo> // For std::bad_cast

using namespace std;

class Animal{
public:
    virtual ~Animal(){}
    int color;
};



class Cat 
//:public Dog
:public Animal
{
public:
    int weight;
};

class Bird 
{
public:
    int voice;
    operator char*(){return const_cast<char*>("Birdy");}
};


class Dog
//:public Cat
:public Animal
{
public:    
    int size;
    Dog(){}    
    //Dog(Cat c){}
    
    operator Bird() {return Bird();}
    operator char*(){return const_cast<char*>("Doggy");}
};



void learn_casts()
{
    int intValue = 1000;
    char charValue = 0;
    
    charValue = static_cast<char>(intValue);
    intValue = static_cast<int>(charValue);
    
    cout << intValue<<endl;
   
    {
        Animal a;
        Dog d;
        Cat c;
        Bird b;
           
        a=static_cast<Animal>(c);
        //d=reinterpret_cast<Dog>(c);
        //b = static_cast<Bird>(d);
        b = d;
        
        cout <<d<<endl;
    }

    {
        Animal a;
        Dog d;
        Cat c;
        Bird b;

        Animal *pa = &a;
        const Animal *pa_const = &a;
        Dog *pd;
        //const Dog *pd_const = &d;
        Cat *pc = &c;
        Bird *pb;

        pd=static_cast<Dog*>(pa);
        //pd=static_cast<Dog*>(pc);
        pd=reinterpret_cast<Dog*>(pc);
        
        //intptr_t intVal = static_cast<intptr_t>(pd);
        //int intVal = reinterpret_cast<int>(pd);
        intptr_t intVal = (intptr_t)pd;        
        
        cout <<"pointer 1: "<<*pd<<endl;
        
        pd=const_cast<Dog*>(static_cast<const Dog*>(pa_const));        
        cout <<"pointer 2: "<<*pd<<endl;
        
        long long longlongVal = 33;
        int iVal = 34;
        unsigned int uiVal = 45;
        float floatVal = 33.0;
        
        //iVal = reinterpret_cast<int>(longlongVal); //error
        iVal = static_cast<int>(longlongVal);
        //longlongVal = reinterpret_cast<long long int>(iVal);
        //iVal = (int)llVal;
        //floatVal = reinterpret_cast<float>(iVal);
        //uiVal = reinterpret_cast<unsigned int>(iVal);
        
        cout <<iVal<<endl;
    }
    
    {
        Dog *d = nullptr;
        Cat *c = nullptr;
        Bird *b = nullptr;
        Animal *a = nullptr;
        
        //d = static_cast<Dog*>(static_cast<void*>(c));
        d = reinterpret_cast<Dog*>(c);
        //b = static_cast<Bird*>(d);
        
    }
    
    {
        Dog dog;
        Cat cat;
        
        Dog *d = nullptr;
        Cat *c = nullptr;
        Bird *b = nullptr;
        Animal *a = &dog;
        

        d = dynamic_cast<Dog*>(a);
        b = dynamic_cast<Bird*>(a);
        
        if(d!=nullptr)
        {
            cout <<*d<<endl;
        }
        else
        {
            cout <<"null\n";    
        }
        
        if(b!=nullptr)
        {
            cout <<*b<<endl;
        }
        else
        {
            cout <<"bird null\n";    
        }        
        
        Animal &aref = cat;
        
        try{
            Dog &dref = dynamic_cast<Dog&>( aref );
        }catch (const std::bad_cast& e) {
            cout <<"catch bad_cast"<<endl;
        }catch(...) {
            cout <<"catch"<<endl;    
        }
    }
}


