
// Function A1
/*

*/
#include <iostream>
#include <math.h>

// Return Point
int* Square(int input)
{
	int* outputData;
	outputData = new int[2];
	outputData[0] = input;
	outputData[1] = input*input;
	return outputData;
}
// Return Value
float Square(float input)
{
	return input * input;
}

//Main
int main()
{
	for (int i(0); i < 10; i++)
	{
		printf("[%d]:[%d]\n", Square(i)[0], Square(i)[1]);
		printf("[%d]:[%f]\n",i, Square((float)i));
	}
	
}