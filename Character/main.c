

#include<stdio.h>
#include<string>
#include<string.h> //strlen()

using namespace std;

// char = char + char
void Example_charConbine(void)
{
	char A[10] = "Hello";
	char B[10] = "World";
	int len = 20;
	char C[20];
	const char* D;
	memset(C, '\0', len);
	strcat(C, A);
	D = A;
	printf("A: %s \nD: %s\n", A, D);
	strcat(C, " ");
	strcat(C, B);
	D = B;
	printf("B: %s \nD: %s\n", B, D);
	D = C;
	printf("C: %s \nD: %s\n", C, D);

	// Release Point
	D = NULL; // miss this will make system crash.
	delete D;
}

// size of a character
int CharacterSize(char* Input)
{
	int i;
	for (i = 0; ; i++)
	{
		if (!Input[i + 1]) break;
	}
	//printf("%d\n", i + 1);
	return i + 1;
}
void SizeOfChar(void)
{
	char CharArray[20] = "12345678901234567";
	char* CharPoint;
	CharPoint = CharArray;
	//CharacterSize(point);
	printf("Size Of a Character: %d\n", CharacterSize(CharPoint));
	
	// Release Point
	CharPoint = NULL; // miss this will make system crash.
	delete CharPoint;
}

int main()
{
	Example_charConbine();
	SizeOfChar();
	return 0;
}
