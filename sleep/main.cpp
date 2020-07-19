// Sleep
#include <stdio.h> // printf()
#include <stdlib.h> 
#include <time.h>
#include <unistd.h> // sleep()
#include <iostream>       // cout cin endl
#include <thread>         // thread
#include <chrono>         // std::chrono::seconds
 

int delay_second(int time_second)
{
    for (int i=0 ; i<time_second ; i++)
    {
        std::this_thread::sleep_for (std::chrono::seconds(1));
        printf("%d\n",i+1);
        //std::this_thread::sleep_for (std::chrono::seconds(time_second)); // Error, can't input a variable
    }
    
    return 1;
}

// Example Function
void example_a()
{
    printf("Delay seconds with thread\n");
    if(delay_second(3))
    {
        printf("Time's up\n");
    }
}

int main() 
{
    example_a();
    return 0;
}