#include <iostream> 
#include <stdio.h>
using namespace std;

template <typename T>
bool Smaller(T a, T b)
{
	if (a < b)
	{
		printf("First Larger than Second\n");
	}
	else
	{
		printf("First Smaller than Second\n");
	}
	return a < b;
}

int main() {
	// Case A
	cout << Smaller(10, 20) << endl;

	// Case B
	cout << Smaller(string("xyz"), string("abc")) << endl;

	return 0;
}