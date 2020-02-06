// Character A1
#include <stdio.h>

int CharacterSize(char* Input)
{
	int i;
	for (i = 0; ; i++)
	{
		if (!Input[i + 1]) break;
	}
	//printf("%d\n", i + 1);
	return i+1;
}

int main()
{
	char CharArray[20] = "12345678901234567";
	char* point;
	point = CharArray;
	//CharacterSize(point);
	printf("%d\n", CharacterSize(point));

	return 0;
}
