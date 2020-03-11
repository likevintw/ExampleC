

#include<stdio.h>
#include <fstream> //printf
#include <iostream> // cout, cin

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

// Argument Passing
//Call by Value
void call_by_value(int a, int b)
{
	a = 5;
	b = 4;
	cout << "In Function call_by_value(): " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n",  a, &a);
	printf(" b=%d, &b=%p\n",  b, &b);
}
//Call by Address
void call_by_adress(int* a, int* b)
{
	*a = 5;
	*b = 4;
	cout << "In Function call_by_Address(): " << endl;
	printf(" *a=%d,a=%p, &a=%p\n", *a, a, &a);
	printf(" *b=%d,b=%p, &b=%p\n", *b, b, &b);
}
//Call by Reference
void call_by_reference(int& a, int& b)
{
	a = 5;
	b = 4;
	cout << "In Function call_by_Reference(): " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);
}
void ArgumentPassing(void)
{
	cout << "Argument Passing Example" << endl;

	//1. Call by Value
	cout << "1. Call by Value" << endl;
	int a(1), b(2);
	cout << "Original: " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);

	call_by_value(1, 2);

	cout << "After call_by_value(): " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);

	//2. Call by Address
	cout << endl << "2. Call by Address" << endl;
	a = 1;
	b = 2;
	cout << "Original: " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);

	call_by_adress(&a, &b);

	cout << "After call_by_Address(): " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);

	//3.Call by Reference
	cout << endl << "3. Call by Reference" << endl;

	a = 1;
	b = 2;
	cout << "Original: " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);

	call_by_reference(a, b);

	cout << "After call_by_reference(): " << endl;
	//printf("*a=%d,a=%d, &a=%p\n", *a, a, &a); //*a error
	//printf("*b=%d,b=%d, &b=%p\n", *b, b, &b); //*b error
	printf(" a=%d, &a=%p\n", a, &a);
	printf(" b=%d, &b=%p\n", b, &b);
}

int main()
{
	/*
	FunctionPointerA();
	FunctionPointerB();
	CallbackFunction();
	CallbackFunctionTypedef();
	ArgumentPassing();
	*/
	ArgumentPassing();
	return 0;
}
