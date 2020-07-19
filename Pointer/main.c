// string + string
// string pointer
#include<stdio.h>
#include<string>
#include<iostream>

using namespace std;

// Unfinished
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
void SecretData::operator=(SecretData& point)
{
	ReferenceNumber++; //left of =,--
	point.ReferenceNumber--; //right of =, ++
}

// Smart Point example online
class Ptr 
{
	int* ptr;
public:
	explicit Ptr(int* p = NULL) { ptr = p; }  // Save pointer
	~Ptr() // recycle pointer
	{
		printf("Release Pointer\n");
		delete(ptr);
	}  
	int& operator *() { return *ptr; }  // override operator
};
void Example_SmartPointer(void)
{
	printf("\nExample_SmartPointer()\n");
	Ptr ptr(new int());
	*ptr = 4;
	cout << *ptr << endl;
	// Recycle pointer automatically
}

// StringPointer
void Example_StringPointer(void)
{
	printf("\nExample_StringPointer()\n");
	string str1, str2;
	str1 = "Hello";
	str1 = str1 + " ";
	str2 = "World";
	str2 = str1 + str2;
	char* charBuffer;
	string* strPoint = new string("Test");
	//string* strPoint = str2;
	printf("Result: str2: %s\n", str2.c_str());
	printf("Result: strPoint: %s\n", strPoint->c_str());
	//printf("Result: strPoint: %s\n", strPoint.c_str()); // error
	delete strPoint;
}

// Value and Address
void Example_ValueAddress(void)
{
	printf("\nExample_ValueAddress()\n");
	int* IntPointerK;
	IntPointerK = NULL;
	IntPointerK = new int(45);
	// Show Address
	printf("IntPointerK = %d\n", *IntPointerK); // The operator of getting value
	printf("&IntPointerK = %p\n", &IntPointerK); // The operator of getting address

	//Release
	delete IntPointerK;
	// Show Error
	//printf("IntPointerK = %d\n", *IntPointerK); // Show Error
	// Show Error
	//printf("&IntPointerK = %p\n", &IntPointerK); // Show Error
}

// One dimension array
void OneDimensionArray(void)
{
	printf("\nOneDimensionArray()\n");
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
}

// Two dimension array
void TwoDimentionArray(void)
{
	printf("\nTwoDimentionArray()\n");
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
			printf("Value [%d][%d]: %d\n", i, j, DynamicArray[i][j]);
			printf("Address [%d][%d]: %p\n", i, j, &DynamicArray[i][j]);
		}
	}

	//Delete DynamicArray, Important
	for (int i(0); i < x; i++)
	{
		delete[] DynamicArray[i];
	}
	delete[] DynamicArray;
}

int main()
{
	Example_StringPointer();
	Example_SmartPointer();
	Example_ValueAddress();
	OneDimensionArray();
	TwoDimentionArray();
	return 0;
}
