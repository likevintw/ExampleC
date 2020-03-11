
// String, String Dislocate
#include<stdio.h>
#include<string>
#include<string.h> //strlen()

using namespace std;
string *StringDislocate(string inputData)
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
int main()
{
	printf("String Dislocation\n");
	string strA = "Hello,World";
	printf("%s\n", strA.c_str());
	printf("%s %s\n", StringDislocate(strA)[0].c_str(), StringDislocate(strA)[1].c_str());
	strA = "r,123";
	printf("%s\n", strA.c_str());
	printf("%s %s\n", StringDislocate(strA)[0].c_str(), StringDislocate(strA)[1].c_str());
	return 0;
}
