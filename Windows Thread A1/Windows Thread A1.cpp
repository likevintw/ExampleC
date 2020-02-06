/*
Tread R1 20190114_1414
20190114_1414 State Machine
20190108_1750 build
*/
#include <windows.h> //for Sleep(100);
#include <iostream>
#include <ctime>
#include <thread>

using namespace std;

short state_code(0);

void state_output()
{
    while(1)
    {
        cout<<"Current State: "<<state_code<<endl;
        Sleep(1500);
    }

}

int main()
{
    thread mThread( state_output ); //Execute the thread

    while(1)
    {
        if(cin>>state_code)
        {
            cout<<"State input"<<endl;
            //cout<<"Current State: "<<state_code<<endl;
        }
    }

     mThread.join(); //Waiting for the end of mThread

    return 0;

}
