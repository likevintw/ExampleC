//
//  main.cpp
//  KevinCPlus
//
//  Created by Kevin on 2019/11/9.
//  Copyright © 2019 Kevin. All rights reserved.
//

/*
2D Array A2
*/

#include <iostream>
#include <fstream>

using namespace std;


int main()
{
    cout << "Read/Write Text File" << endl;

    // Set Raw and Colume Size
    unsigned int x(3),y(5);
    
    // Create DynamicArray
    short **DynamicArray= new short *[x];
    for(int i(0);i<x;i++)
    {
        DynamicArray[i] = new short [y];
    }
    
    // Set DynamicArray Data
    unsigned int n=1;
    for(int i(0);i<x;i++)
    {
        for(int j(0);j<y;j++)
         {
             DynamicArray[i][j]=n;
             n++;
         }
    }
    for(int i(0);i<x;i++)
    {
        for(int j(0);j<y;j++)
         {
             printf("DynamicArray[%d][%d]: %d\n",i,j,DynamicArray[i][j]);
         }
    }
    
    //Delete DynamicArray, Important
    for(int i(0);i<x;i++)
    {
        delete[] DynamicArray[i] ;
    }
    delete[] DynamicArray;

    return 0;
}
