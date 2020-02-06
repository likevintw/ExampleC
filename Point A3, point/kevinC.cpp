

// Point A3, point

#include <iostream>



int main()
{
	printf("\n");
	printf("Point Example\n");
	// One Dimension Array Example
	int* IntPointerK;
	IntPointerK = NULL;
	IntPointerK = new int (45);
	printf("IntPointerK = new int (45);\n");
	// Show Value and Address
	printf("IntPointerK = %p\n", IntPointerK); 
	printf("*IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address
	
	// Error
	printf("\n");
	printf("IntPointerK = a;  >> Error \n");
	/*
	int a = 45;
	IntPointerK = a; // Error
	// Show Value and Address
	printf("*IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address
	*/

	// Error
	printf("\n");
	printf("IntPointerK = *a;  >> Error \n");
	/*
	int a = 45;
	IntPointerK = *a; // Error
	// Show Value and Address
	printf("*IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address
	*/

	// 
	printf("\n");
	int a = 45;
	IntPointerK = &a;
	printf("IntPointerK = &a;\n");
	// Show Value and Address
	printf("a = %d\n", a);
	printf("*a = Error\n");
	printf("&a = %p\n", &a);
	printf("*IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address

	// 
	printf("\n");
	printf("IntPointerK = new int [2];\n");
	IntPointerK = new int [2];
	IntPointerK[0] = 1;
	IntPointerK[1] = 2;
	// Show Value and Address
	printf("IntPointerK = %p\n", IntPointerK); // The operator of getting value
	printf("*IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address
	printf("\n");
	for (int i(0); i < 2; i++)
	{
		printf("IntPointerK[%d] = %d\n",i, IntPointerK[i]); // The operator of getting value
		printf("*IntPointerK[%d] = Error\n", i); // The operator of getting value
		printf("&IntPointerK[%d] = %p\n",i, &IntPointerK[i]); // The operator of getting address
		printf("\n");
	}
	

	

	return 0;
}