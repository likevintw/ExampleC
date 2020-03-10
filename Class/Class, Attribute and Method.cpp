//
//  main.cpp
//  KevinCPlus
//
//  Created by Kevin on 2019/11/9.
//  Copyright © 2019 Kevin. All rights reserved.
//

#include <iostream>

class Car
{
public:
    //Attribute
    std::string *color;
    float speed;
    //Method
    Car();
    void ShowCarSpeed();
    void ShowCarColor();
};

Car::Car()
{
    speed=0.6;
}
void Car::ShowCarColor()
{
    printf("The Car Color is %s\n",color);
}
void Car::ShowCarSpeed()
{
    printf("The Car Speed is %f\n",speed);
}
int main(int argc, const char * argv[])
{
    // insert code here...
    std::cout << "Class Example\n";
    
    //
    Car carA;
    std::string DataBuffer="Red";
    carA.color=&DataBuffer;
    carA.speed=11.1;
    carA.ShowCarSpeed();
    carA.ShowCarColor();
    
    Car carB;
    DataBuffer="Blue";
    carB.color=&DataBuffer;
    carB.speed=11.1;
    carB.ShowCarSpeed();
    carB.ShowCarColor();
    
    return 0;
}
