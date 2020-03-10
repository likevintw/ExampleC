

#include <iostream> //Import file
#include <fstream> //printf


void A()
{
	printf("Hello A\n");
}
void B()
{
	printf("Hello B\n");
}
int main()
{
	void (*Test[])() = {A,B};
	
	for (int i(0); i < 2; i++)
	{
		Test[i]();
		printf("Address of Test[%d]: %d\n", i, (int)Test[i]);
	}
	return 0;
}