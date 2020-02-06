/*****************
Class: constructor&deconstructor R1 20190208_0034

First constructor, last deconstructor

*****************/
#include <iostream> //cout and cin

using namespace std;

class A
{
public:
    A(){cout<<"The Constructor of A"<<endl;};
    ~A(){cout<<"The Deconstructor of A"<<endl;};
};

class B
{
public:
    B(){cout<<"The Constructor of B"<<endl;};
    ~B(){cout<<"The Deconstructor of B"<<endl;};
};

class C
{
public:
    C(){cout<<"The Constructor of C"<<endl;};
    ~C(){cout<<"The Deconstructor of C"<<endl;};
};

class D
{
public:
    D(){cout<<"The Constructor of D"<<endl;};
    ~D(){cout<<"The Deconstructor of D"<<endl;};
};


int main()
{
       cout<<"Random Number R3 Example"<<endl;
       cout<<endl;
       A A;
       B B;
       C C;
       D D;

       return 0;
}
