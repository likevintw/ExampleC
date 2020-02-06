/*
Argument Passing
20190109_2004

Address and Reference Passing will
change the values when that passing
through the function, but the value
passing will not.

So, you don't return the value when
you are using Address and Reference
Passing.


*/
#include <iostream>

using namespace std;

//Call by Value
void call_by_value(int a, int b)
{
       a=5;
       b=4;
       cout<<"In Function call_by_value(): "<<endl<<" a= "<<a<<" b= "<<b<<endl;
}

//Call by Address
void call_by_adress(int *a, int *b)
{
       *a=5;
       *b=4;
       cout<<"In Function call_by_Address(): "<<endl<<" a= "<<*a<<" b= "<<*b<<endl;
}

//Call by Reference
void call_by_reference(int &a, int &b)
{
       a=5;
       b=4;
       cout<<"In Function call_by_Reference(): "<<endl<<" a= "<<a<<" b= "<<b<<endl;
}
int main()
{
    cout<<"Argument Passing Example"<<endl;

    //1. Call by Value
    cout<<"1. Call by Value"<<endl;
    int a(1),b(2);
    cout<<"Original: "<<endl<<" a= "<<a<<" b= "<<b<<endl;
    
    call_by_value(1,2);
    cout<<"After call_by_value(): "<<endl<<" a= "<<a<<" b= "<<b<<endl;

    //2. Call by Address
    cout<<endl<<"2. Call by Address"<<endl;
    a=1;
    b=2;
    cout<<"Original: "<<endl<<" a= "<<a<<" b= "<<b<<endl;
    call_by_adress(&a,&b);
    cout<<"After call_by_Address(): "<<endl<<" a= "<<a<<" b= "<<b<<endl;

    //3.Call by Reference
    cout<<endl<<"3. Call by Reference"<<endl;
    a=1;
    b=2;
    cout<<"Original: "<<endl<<" a= "<<a<<" b= "<<b<<endl;
    call_by_reference(a,b);
    cout<<"After call_by_reference(): "<<endl<<" a= "<<a<<" b= "<<b<<endl;
    
    return 0;

}


