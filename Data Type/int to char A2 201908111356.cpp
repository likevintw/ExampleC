/*
int to char A2 201908111356
*/

#include <fstream>


char* itobs(short n ) 
{
	char *ps=new char [8 * sizeof(short) + 1];
	int size = 8 * sizeof(short);
	int i = size - 1;
	while (i + 1) 
	{
		ps[i--] = (1 & n) + '0';
		n >>= 1;
	}
	ps[size] = '\0';
	return ps;
}
int main()
{
	
	for (int i(-5); i < 5; i++)
	{
		printf("%d = %s\n", i, itobs(i));
	}

	printf("End");
	return 0;
}
