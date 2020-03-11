
// String, String Dislocate
#include<stdio.h>
#include<string>
#include<string.h> //strlen()

using namespace std;
// String Dislocate Case 1
string *StringDislocate_2Dots(string inputData)
{
	int len = inputData.size();
	//printf("String Length: %d\n", len);
	int DotLocation;
	// 
	for (int i(0); i < len; ++i)
	{
		if (inputData.c_str()[i] == ',')
		{
			//printf("DotLocation=%d\n", i);
			DotLocation = i ;
		}
		//printf("%c\n", inputData.c_str()[i]);
	}
	string* result = new string[2];
	for (int i(0),j(0); i < len+1; ++i)
	{
		if (i< DotLocation)
		{
			result[0] = result[0] + inputData.c_str()[i];
			++j;
		}
		if (i == DotLocation)
		{
			j = 0;
		}
		if (i > DotLocation)
		{
			result[1]= result[1]+ inputData.c_str()[i];
			++j;
		}
	}
	//printf("A:%s  B:%s\n", result[0].c_str(), result[1].c_str());
	return result;
}
void Example_StringDislocate_2Dot(void)
{
	printf("\nExample_StringDislocate_2Dot()\n");
	string strA = "Hello,World";
	printf("Input: %s\n", strA.c_str());
	printf("Output: %s\n", StringDislocate_2Dots(strA)[0].c_str());
	printf("Output: %s\n", StringDislocate_2Dots(strA)[1].c_str());
	strA = "r,123";
	printf("Input: %s\n", strA.c_str());
	printf("Output: %s\n", StringDislocate_2Dots(strA)[0].c_str());
	printf("Output: %s\n", StringDislocate_2Dots(strA)[1].c_str());
}

// String Dislocate Case 2
struct LinkList
{
	string StringInfo;
	LinkList* node;
};
LinkList* StringDislocate(string inputData)
{
	printf("input: %s\n", inputData.c_str());
	int len = inputData.size();
	//printf("String Length: %d\n", len);
	LinkList* headNode = NULL;
	LinkList* lastNode = NULL;
	
	string strBuffer;
	// Get the location of dots. 
	for (int i(0); i < len+1; ++i)
	{
		if ((inputData.c_str()[i] == ',')||i==len)
		{
			LinkList* current = new LinkList;
			current->StringInfo = strBuffer;
			strBuffer = "";
			if (headNode == NULL)
			{
				headNode = current;
				lastNode = current;
			}
			else
			{
				lastNode->node = current;
				lastNode = current;
			}
		}
		else
		{
			strBuffer = strBuffer + inputData.c_str()[i];
		}
		//printf("%d,%s\n", i, strBuffer.c_str());
	}

	// Show all the location of dots
	/*
	printf("Result\n");
	lastNode = headNode;
	while (lastNode)
	{
		printf("%s\n", lastNode->StringInfo.c_str());
		lastNode = lastNode->node;
	}*/
	
	return headNode;
}
void Example_StringDislocate(void)
{
	printf("\nExample_StringDislocate()\n");
	LinkList* Result;
	Result = StringDislocate("Hello,World,Yo");
	printf("Output:\n");
	while (Result)
	{
		printf("%s\n", Result->StringInfo.c_str());
		Result = Result->node;
	}
}

// String Example
void Example_String(void)
{
	printf("\nExample_String()\n");
	string str1, str2;
	str1 = "Hello";
	str1 = str1 + " ";
	str2 = "World";
	str2 = str1 + str2;

	string* strPoint = new string("Test");
	//string* strPoint = str2;
	printf("Result: str2: %s\n", str2.c_str());
	printf("Result: strPoint: %s\n", strPoint->c_str());
	//printf("Result: strPoint: %s\n", strPoint.c_str()); // error
	delete strPoint;
}

// string pointer
void Example_StringPointer(void)
{
	printf("\nExample_StringPointer()\n");
	// integer pointer
	int* intPointer = new int;
	*intPointer = 99;
	printf("intPointer Value = %d\n", *intPointer);
	printf("intPointer Address = %p\n", &intPointer);
	printf("\n");
	// character pointer
	char charBuffer[] = "Good";
	char* charPointer = new char;
	//*charPointer = "Good"; // Error
	charPointer = charBuffer;
	//printf("charPointer Value = %c\n", *charPointer); // print "G"
	//printf("charPointer Value = %s\n", *charPointer); // Error, memory crash
	printf("charPointer Value = %s\n", charPointer);
	printf("charPointer Address = %p\n", &charPointer);
	printf("\n");
	// String pointer
	string* stringPointer = new string(); // not new string;
	*stringPointer = "Hello";
	printf("stringPointer: %s\n", stringPointer->c_str()); // not .c_str()
	//printf("stringPointer: %s\n", *stringPointer); // Will show wrong data
	printf("stringPointer: %p\n", &stringPointer);
}

int main()
{
	Example_StringDislocate_2Dot();
	Example_StringDislocate();
	Example_String();
	Example_StringPointer();
	return 0;
}
