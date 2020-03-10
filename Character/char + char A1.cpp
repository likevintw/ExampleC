// string + string
#include<stdio.h>
#include<string>

using namespace std;

int main()
{
	char A[10] = "Hello";
	char B[10] = "World";
	int len = 20;
	char C[20];
	memset(C, '\0', len);
	strcat(C, A);
	strcat(C, " ");
	strcat(C, B);
	printf("%s\n", C );
	return 0;
}
