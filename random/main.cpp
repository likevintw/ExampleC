#include <stdio.h> // printf()
#include <stdlib.h> 
#include <time.h>
#include <unistd.h> // sleep()

int randomRange(int min, int max)
{
    return ( rand() % ( max - min ) ) + min;
}

int *create_random_sequence(int data_size)
{
    // Create a random squence
    int *random_sequence = new int [data_size]; 
    for(int i=0; i<data_size; i++)
    {
        random_sequence[i] = -1;
    }
    for(int i=0,j=0 ; i<data_size ;)
    {
        j = randomRange(0,data_size);
        if (random_sequence[j] == -1)
        {
            random_sequence[j] = i;
            i++;
            //printf("%d,%d\n",j,i);
        }
    } 
    return random_sequence;
}

int main(void) 
{ 
    int random_number = 0;
    // Create a random squence
    int data_size = 10;
    int *random_sequence = create_random_sequence(data_size);
    for(int i = 0; i<data_size; i++) 
    {
        printf("%d\n",random_sequence[i]);
    }
    return 0; 
} 