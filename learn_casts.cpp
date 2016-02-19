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
        Dog d;
        Cat c;
        Bird b;
           
        //d=static_cast<Dog>(c);
        //d=reinterpret_cast<Dog>(c);
        //b = static_cast<Bird>(d);
        b = d;
        
        cout <<d<<endl;
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
        
        if(d!=nullptr)
        {
            cout <<*d<<endl;
        }
        else
        {
            cout <<"null\n";    
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


