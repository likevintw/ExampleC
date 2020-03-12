

// Point A3, point

#include <iostream>
#include <stdio.h>	// printf()
#include <string.h>	// strcpy, strcpy 
#include <stdlib.h> // malloc, free, rand 

void Example_new_value(void)
{
	printf("Point, new example\n");

	// define a int point
	int* IntPointerK;
	IntPointerK = NULL;
	IntPointerK = new int(45);
	printf("IntPointerK = new int (45);\n");
	// Show Value and Address
	printf("*IntPointerK = %d\n", *IntPointerK);	// Got value
	printf("IntPointerK = %p\n", IntPointerK);		// value
	printf("&IntPointerK = %p\n", &IntPointerK);	// address

	// Define a interger
	int a = 99;
	// Show Value and Address
	printf("int a = %d\n", a);
	printf("*a >> error\n");	// Got value, error
	printf("a = %d\n", a);		// value
	printf("&a = %p\n", &a);	// address

	// To get the value
	printf("\nTo get the value\n");
	printf("*IntPointerK = a\n");
	//IntPointerK = a; // Error
	//IntPointerK = a; // Error
	*IntPointerK = a;
	// Show Result
	printf("*IntPointerK = %d, a=%d\n", *IntPointerK,a); // *IntPointerK
	printf("IntPointerK = %p, &a=%p \n", IntPointerK, &a); // IntPointerK
	printf("&IntPointerK = %p, &a=%p\n", &IntPointerK,&a); // &IntPointerK

	// To point address
	printf("\nTo point address\n");
	printf("IntPointerK = &a\n");
	//IntPointerK = a; // Error
	//IntPointerK = a; // Error
	IntPointerK = &a;
	// Show Result
	printf("*IntPointerK = %d, a=%d\n", *IntPointerK, a); // *IntPointerK
	printf("IntPointerK = %p, &a=%p \n", IntPointerK, &a); // IntPointerK
	printf("&IntPointerK = %p, &a=%p\n", &IntPointerK, &a); // &IntPointerK

	// To get address
	//&IntPointerK = &a; >> error, the struecture of a pointer and a constant are not the same
	
	IntPointerK = NULL;
	delete IntPointerK;

}
void Example_new_array(void)
{
	// 
	printf("\n");
	printf("IntPointerF = new int [2];\n");
	int* IntPointerF = new int[2];
	IntPointerF[0] = 9;
	IntPointerF[1] = 8;
	printf("*IntPointerF = %d\n", *IntPointerF);
	printf("IntPointerF = %p\n", IntPointerF);
	printf("&IntPointerF = %p\n", &IntPointerF);
	printf("\n");
	/**/
	//printf("*IntPointerF[%d] = %d\n", 0, *IntPointerF[0]); // error
	printf("IntPointerF[%d] = %d\n", 0, IntPointerF[0]);
	printf("&IntPointerF[%d] = %p\n", 0, &IntPointerF[0]);
	printf("\n");
	//
	//printf("*IntPointerF[%d] = %d\n", 1, *IntPointerF[1]);
	printf("IntPointerF[%d] = %d\n", 1, IntPointerF[1]);
	printf("&IntPointerF[%d] = %p\n", 1, &IntPointerF[1]);
	printf("\n");
	

	IntPointerF = NULL;
	delete IntPointerF;
}
void Example_malloc_value(void)
{
	int* p = (int*)malloc(sizeof(int));

	*p = 199;
	printf("Pointer Value: %d\n", *p);
	printf("Pointer Address: %p\n", p);

	*p = 299;
	printf("Pointer Value: %d\n", *p);
	printf("Pointer Address: %p\n", p);

	p = NULL;
	free(p);

}
void Example_malloc_array(void)
{
	int size = 10;

	int* arr = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) 
	{
		arr[i] = i;
		printf("arr[%d]: %d\n", i, arr[i]);
	}


	arr = NULL;
	free(arr);
}
void Example_realloc(void)
{
	/* Initial memory allocation */
	char* str = (char*)malloc(sizeof(char));
	strcpy(str, "yiibai");
	printf("String = %s,  Address = %p\n", str, str);

	/* Reallocating memory */
	char* str2 = (char*)realloc(str, 25);
	strcpy(str2, ".com");
	printf("String = %s,  Address = %p\n", str2, str2);

	str = NULL;
	free(str);

	str2 = NULL;
	free(str2);
}

int main()
{
	/*
	Example_new_value();
	Example_new_array();
	Example_malloc_value();
	Example_malloc_array();
	Example_realloc();
	*/

	Example_realloc();
	return 0;
}