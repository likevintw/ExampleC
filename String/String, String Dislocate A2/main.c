
// String, String Dislocate
#include<stdio.h>
#include<string>
#include<string.h> //strlen()

using namespace std;
// Case 1
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

// Case 2
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
	/**/
	printf("Result\n");
	lastNode = headNode;
	while (lastNode)
	{
		printf("%s\n", lastNode->StringInfo.c_str());
		lastNode = lastNode->node;
	}
	
	return headNode;
}
int main()
{
	// Case 1
	/**/
	printf("String Dislocation\n");
	string strA = "Hello,World";
	printf("%s\n", strA.c_str());
	printf("%s %s\n", StringDislocate_2Dots(strA)[0].c_str(), StringDislocate_2Dots(strA)[1].c_str());
	strA = "r,123";
	printf("%s\n", strA.c_str());
	printf("%s %s\n", StringDislocate_2Dots(strA)[0].c_str(), StringDislocate_2Dots(strA)[1].c_str());
	

	// Case 2
	LinkList* Result;
	Result=StringDislocate("Hello,World,Yo");
	while (Result)
	{
		printf("%s\n", Result->StringInfo.c_str());
		Result = Result->node;
	}

	return 0;
}
