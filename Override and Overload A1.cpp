

//Override and Overload
/*
Override:
Re-ride the functions which are inherited from other class. 

Overload:
More than two functions have the same name, but with different input parameters
*/

#include<Windows.h>
#include<fstream>

class Hello
{
public:
	void sayHello()
	{
		printf("Hello\n");
	}
};

class Mandarin : Hello
{
public:
	void sayHello()
	{
		printf("你好\n");
	}
};

class English : Hello
{
public:
	void sayHello()
	{
		printf("Hello\n");
	}
};


//Overload
class overloadExample
{
public:
	void showType(int inputData)
	{
		printf("Interger Type\n");
	}
	void showType(float inputData)
	{
		printf("Float Type\n");
	}
};
int main()
{

	// Override Example
	printf("Override Example\n");
	//
	Mandarin helloA;
	helloA.sayHello();
	//
	English helloB;
	helloB.sayHello();


	//Overload Example
	printf("Overload Example\n");
	overloadExample Example1;
	char DataBuffer(22);
	Example1.showType((int)DataBuffer);
	Example1.showType((float)DataBuffer);


	system("pause");
	return 0;
}

