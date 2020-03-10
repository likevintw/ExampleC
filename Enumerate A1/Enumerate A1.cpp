

// enum, enumerate
/*
1. Enhance and install of the define function.
2. Using enum with swich finction
*/
#include<Windows.h>
#include<fstream>

enum WeekDay
{
	MON = 1, TUE, WED, THU, FRI, SAT, SUN
};

enum alphabetToScore
{
	F=0,E,D,C,B,A
};

int main()
{

	// 
	printf("Example\n");
	//Case1
	WeekDay weekA;
	weekA = FRI;
	printf("Friday number is %d\n", weekA);
	
	//Case 2
	char TestScore(0);
	alphabetToScore ScoreA;
	ScoreA = C;
	TestScore = (ScoreA-1) * 10 + 50;
	
	printf("C Score is %d\n", TestScore);

	system("pause");
	return 0;
}

