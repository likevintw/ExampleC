
// Call Back Function
#include<stdio.h>
int Add (int a, int b) {
	return a+ b;
}

int Mutiple(int a, int b) {
	return a * b;
}

int main(void) {
	int (*FunctionPoint)(int, int);
	int a = 1, b = 2;
	FunctionPoint = Add;
	printf("%d + %d = %d\n", a,b,FunctionPoint(a, b));
	FunctionPoint = Mutiple;
	printf("%d * %d = %d\n", a, b, FunctionPoint(a, b));
	return 0;
}