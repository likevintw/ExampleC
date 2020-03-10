

// Function Point A4
#include <fstream> //printf

// Case B
void A()
{
	printf("Hello A\n");
}
void B()
{
	printf("Hello B\n");
}
void CaseA()
{
	printf("\n");
	printf("Case A\n");
	void (*Test[])() = { A,B };

	for (int i(0); i < 2; i++)
	{
		Test[i]();
		printf("Address of Test[%d]: %d\n", i, (int)Test[i]);
	}
}

//Case B
int add(int a, int b)
{
	return a + b;
}
int mutiple(int a, int b)
{
	return a * b;
}
void CaseB()
{
	printf("\n");
	printf("Case B\n");
	int (*FunctionArray[])(int,int) = { add,mutiple };
	for (int i(0); i < 2; i++)
	{
		printf("FunctionArray[%d]= %d\n", i, FunctionArray[i](5, 6));
	}
}

// Case C
typedef int (*MathMethod)(int, int); // define a function point type

int Mul(int a, int b) { return a * b; }
int Divide(int a, int b) { return a / b; }
int Minus(int a, int b) { return a - b; }
int Add(int a, int b) { return a + b; }

int Calc(int x, int y, MathMethod Opt) {return Opt(x, y);}

void CaseC()
{
	printf("\n");
	printf("Case C\n");
	int a = 12, b = 7;
	printf("a= %d, b= %d\n",a,b);
	printf("a x b = %d\n", Calc(a, b, Mul));
	printf("a / b = %d\n", Calc(a, b, Divide));
	printf("a + b = %d\n", Calc(a, b, Minus));
	printf("a - b = %d\n", Calc(a, b, Add));
}
int main()
{
	printf("Function Point Example\n");
	CaseA();
	CaseB();
	CaseC();

	return 0;
}