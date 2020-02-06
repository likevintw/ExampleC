
// Call Back Function
#include<stdio.h>

// Create a new type
typedef int (*FunctionPointB)(int, int);

int Add (int a, int b) {
	return a+ b;
}

int Mutiple(int a, int b) {
	return a * b;
}

int main(void) 
{
	// Case 1
	int (*FunctionPoint)(int, int);
	int a = 1, b = 2;
	FunctionPoint = Add;
	printf("%d + %d = %d\n", a,b,FunctionPoint(a, b));
	FunctionPoint = Mutiple;
	printf("%d * %d = %d\n", a, b, FunctionPoint(a, b));

	// Case 2
	FunctionPointB TestPointA;
	TestPointA = Add;
	printf("%d + %d = %d\n", a, b, TestPointA(a, b));
	FunctionPoint = Mutiple;
	printf("%d * %d = %d\n", a, b, FunctionPoint(a, b));

	return 0;
}