

// Point A2, New and Delete

#include <iostream>

class SecretData
{
public:
	int Index;
	int ReferenceNumber;
	SecretData();
	void operator=(SecretData& point);
};
SecretData::SecretData()
{
	Index = 0;
	ReferenceNumber = 0;
}
/**/
void SecretData::operator=(SecretData& point)
{
	ReferenceNumber++; //left of =,--
	point.ReferenceNumber--; //right of =, ++
}


int main()
{
	printf("\n");
	printf("Integer Point Example\n");
	// One Dimension Array Example
	int* IntPointerK;
	IntPointerK = NULL;
	IntPointerK = new int (45);
	// Show Address
	printf("IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address

	//Release
	delete IntPointerK;
	// Show Error
	//printf("IntPointerK = %d\n", *IntPointerK); // Show Error
	// Show Error
	//printf("&IntPointerK = %p\n", &IntPointerK); // Show Error

	printf("\n");
	printf("Integer Point Example B \n");
	// One Dimension Array Example
	int a(45);
	int* IntPointerB;
	IntPointerB = NULL;
	IntPointerB = &a;
	// Show Address
	printf("IntPointerB = %d\n", *IntPointerB); // The operator of getting value
	printf("&IntPointerB = %p\n", &IntPointerB); // The operator of getting address
	//Release
	//delete IntPointerB;
	// Show Error
	//printf("IntPointerB = %d\n", *IntPointerB); // Show Error
	// Show Error
	//printf("&IntPointerB = %p\n", &IntPointerB); // Show Error


	printf("\n");
	printf("One Dimension Array Example\n");
	// One Dimension Array Example
	int* IntPointerA;
	IntPointerA = NULL;
	IntPointerA = new int[2];
	// Set Value
	for (int i(0); i < 2; i++)
	{
		IntPointerA[i] = i + 5;
	}
	// Show Address
	for (int i(0); i < 2; i++)
	{
		printf("IntPointerA[%d] = %d\n", i, IntPointerA[i]);
		printf("&IntPointerA[%d] = %p\n", i, &IntPointerA[i]);
	}
	//Release
	delete[]IntPointerA; //
	// Value and Address
	for (int i(0); i < 2; i++)
	{
		// Show Error
		//printf("IntPointerA[%d] = %d\n", i, IntPointerA[i]); //Show Error
		//printf("&IntPointerA[%d] = %p\n", i, &IntPointerA[i]); //Show Error
	}
	
	printf("\n");
	printf("Two Dimensions Dynamic Array Example\n");
	// Two Dimensions Dynamic Array
	// Create DynamicArray
	//Size
	int x = 3;
	int y = 2;
	short** DynamicArray = new short* [x];
	for (int i(0); i < x; i++)
	{
		DynamicArray[i] = new short[y];
	}

	// Set DynamicArray Data
	unsigned int n = 1;
	for (int i(0); i < x; i++)
	{
		for (int j(0); j < y; j++)
		{
			DynamicArray[i][j] = n;
			n++;
		}
	}
	// Show Array Values
	for (int i(0); i < x; i++)
	{
		for (int j(0); j < y; j++)
		{
			printf("DynamicArray[%d][%d]: %d\n", i, j, DynamicArray[i][j]);
			printf("DynamicArray[%d][%d]: %p\n", i, j, &DynamicArray[i][j]);
		}
	}

	//Delete DynamicArray, Important
	for (int i(0); i < x; i++)
	{
		delete[] DynamicArray[i];
	}
	delete[] DynamicArray;


	// Show Array Values
	// Error
	/*
	for (int i(0); i < x; i++)
	{
		for (int j(0); j < y; j++)
		{
			printf("DynamicArray[%d][%d]: %d\n", i, j, DynamicArray[i][j]);// Error
			printf("DynamicArray[%d][%d]: %p\n", i, j, &DynamicArray[i][j]);// Error
		}
	}*/

	return 0;
}