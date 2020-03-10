// string + string
// string pointer
#include<stdio.h>
#include<string>

using namespace std;

int main()
{
	string str1, str2;
	str1 = "Hello";
	str1 = str1 + " ";
	str2 = "World";
	str2 = str1 + str2;
	char *charBuffer;
	string* strPoint=new string("Test");
	//string* strPoint = str2;
	printf("Result: str2: %s\n", str2.c_str());
	printf("Result: strPoint: %s\n", strPoint->c_str());
	//printf("Result: strPoint: %s\n", strPoint.c_str()); // error
	delete strPoint;
	return 0;
}
