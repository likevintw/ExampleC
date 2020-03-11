

//int to char A1 201908081156

/**/
#include <fstream> //ofstream
#include <time.h> //for time()
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")
#include <math.h>

char *IntToBite(int value) //did not trial yet
{
	char *src = new char[4];
	src[0] = (char)((value >> 24) & 0xFF);
	src[1] = (char)((value >> 16) & 0xFF);
	src[2] = (char)((value >> 8) & 0xFF);
	src[3] = (char)(value & 0xFF);
	for (int i(0); i < 4; i++)
	{
		printf("src[%d] = %c \n", i, src[i]);
	}
	return src;
}

int main()
{
	/*

	&	 AND	
	|	 OR	
	^	 XOR	
	<<	left shift
	>>	right shift
	~	1的補數

	c? p1: p2 equals if(c) p1 else p2
	example: (x==0) ? 0 : 1/x;
	*/
	//Determin a number which is a square of 2 or not.
	/*
	printf("Determin a number which is a square of 2 or not\n");
	int a(256);
	if ((a & -a) == a) printf("%d is the square of 2\n",a);
	else printf("%d is NOT the square of 2\n",a);
	*/

	//Int To Bit
	char buffer[9];
	char upper4bits(0), lower4bits(0);
	short i(0), j(0);
	//input
	i = 245;
	_itoa(i, buffer, 2);
	printf("Input: %d (radix 2): %s\n", i, buffer);

	//lower 4 bits
	j = i >> 4;
	upper4bits = char(j);
	_itoa(j, buffer, 2);
	printf("upper 4 bits: %d (radix 2): %s\n", upper4bits, buffer);

	//lower 4 bits
	j = i & 15;
	lower4bits = char(j);
	_itoa(j, buffer,2);
	printf("lower 4 bits: %d (radix 2): %s\n", lower4bits, buffer);

	return 0;
}


