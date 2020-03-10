// Static A1
#include <stdio.h>

// Case A
/*
initial 1 time.
Not goin on to be released when the function is finished.
It is very similar with a globle varience
*/
void A()
{
	static int countA = 0;
	countA++;
	printf("Function A: %d\n",countA);
}

// Case B
class B
{
public:
	static int CounterB;
};
int B::CounterB = 3;
int main()
{
	// Case A
	for (int i(0); i < 8; i++)
	{
		A();
	}
	
	//B
	/*
	B is a class
	TestB is a object
	An instance is an object in memory.
	static int CounterB; is the varience of class B
	*/
	B::CounterB = 4;
	printf("B::CounterB: %d\n", B::CounterB);
	B TestB;
	TestB.CounterB = 8;
	printf("TestB.CounterB: %d\n", TestB.CounterB);

	//C

	return 0;
}

