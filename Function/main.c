

#include<stdio.h>
#include <fstream> //printf

using namespace std;

// Example Function
int Add(int a, int b) { return a + b; }
int Mutiple(int a, int b) { return a * b; }
int Subtraction(int a, int b) { return a - b; }

//function pointer, CaseA
void A()
{
	printf("A()\n");
}
void B()
{
	printf("B()\n");
}
void FunctionPointerA(void)
{
	printf("\nFunctionPointer()\n");
	void (*Test[])() = { A,B };

	for (int i(0); i < 2; i++)
	{
		Test[i]();
		printf("Address of Test[%d]: %p\n", i, &Test[i]);
	}
}

//function pointer, CaseB
void FunctionPointerB(void)
{
	printf("\n");
	printf("Case B\n");
	int (*FunctionArray[])(int, int) = { Add,Mutiple };
	for (int i(0); i < 2; i++)
	{
		printf("FunctionArray[%d]= %d\n", i, FunctionArray[i](5, 6));
	}
}
// Callback function
void CallbackFunction(void)
{
	printf("\nCallbackFunction()\n");
	int (*FunctionPoint)(int, int);
	int a = 1, b = 2;
	FunctionPoint = Add;
	printf("%d + %d = %d\n", a, b, FunctionPoint(a, b));
	FunctionPoint = Mutiple;
	printf("%d * %d = %d\n", a, b, FunctionPoint(a, b));
}

// Callback function with typedef
typedef int (*FunctionPointB)(int, int);
void CallbackFunctionTypedef(void)
{
	printf("\nCallbackFunctionTypedef()\n");
	int a = 5, b = 7;
	FunctionPointB TestPointA;
	TestPointA = Add;
	printf("%d + %d = %d\n", a, b, TestPointA(a, b));
	TestPointA = Subtraction;
	printf("%d - %d = %d\n", a, b, TestPointA(a, b));
}

// input and return string pointer

int main()
{
	FunctionPointerA();
	FunctionPointerB();
	CallbackFunction();
	CallbackFunctionTypedef();
	return 0;
}
