
/*
1. self-calling
2. && will break when the condition is not fit
*/
#include<stdio.h>
int Sum(int n)
{
	int sum = n;
	bool b = (n > 0) && (sum += Sum(n - 1)); // 2 and 1
	return sum;
}
#define MAX(x,y) (x)>(y)?(x):(y);
#define MINI(x,y) (x)<(y)?(x):(y);
int* MaxCommondFactor(int*p)
{
	//printf("%d %d\n", p[0], p[1]);
	int buffer = MAX(p[0], p[1]);
	p[1] = MINI(p[0], p[1]);
	p[0] = buffer% p[1];
	bool b = ((p[0] != 0)&& (buffer != 0) && (MaxCommondFactor(p)!=0));
	p[0] = buffer;
	return p;
}
int main()
{
	printf("Recursive Example\n");

	/*SumValue*/
	printf("\n1.Sum\n");
	int input(10);
	int output(0);
	output = Sum(input);
	printf("The Sum from 1 to %d= %d\n",input, output);

	/*MaxCommondFactor*/
	printf("\n2.The Maximum Commond Factor\n");
	int* inputData = new int[2];
	inputData[0] = 2*45*33;
	inputData[1] = 3*15*9;
	printf("input: %d, %d\n", inputData[0], inputData[1]);
	inputData = MaxCommondFactor(inputData);
	printf("Answer: %d\n", inputData[1]);
	return 0;
}