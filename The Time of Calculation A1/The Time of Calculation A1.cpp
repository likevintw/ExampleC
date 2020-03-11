/*
The Time of Calculation R1 20190108_1623

20190108_1538
The Time of Calculation R1
Time delay

*/
#include <windows.h>
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    clock_t calculation_time;

    calculation_time=clock(); //Start

    //Make a time delay
    /*
    for(int i(0);i<1000;i++)
        for(int j(0);j<99999;)
    {
        j++;
    }
    */

    Sleep(998); //include<window.h>, in other OS, it needs different header.

    calculation_time=clock()-calculation_time;//End

    cout<<"The Time of Calculation: "<<(float)calculation_time/CLOCKS_PER_SEC<<" second"<<endl;

    return 0;

}
