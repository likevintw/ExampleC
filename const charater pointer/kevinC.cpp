// const char
#include<stdio.h>
#include<string>

using namespace std;

int main()
{
	char A[10] = "Hello";
	char B[10] = "World";
	int len = 20;
	char C[20];
	const char *D;
	memset(C, '\0', len);
	strcat(C, A);
	D = A;
	printf("%s \n%s\n", A, D);
	strcat(C, " ");
	strcat(C, B);
	D = B;
	printf("%s \n%s\n", B, D);
	D = C;
	printf("%s \n%s\n", C,D );
	return 0;
}
