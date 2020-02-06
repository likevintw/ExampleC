
// Inheritance
/*
1. Single Inheritance: AAA inherits AA, AA inherits A.
2. Multiple inheritance: BC inherits BA and BB.
3. Virtul inheritance: CD virtual inherits CB and CC, CC virtual inherits CA, CB virtual inherits CA.
4. RepeatInheritance: CD inherits CB and CC, CC inherits CA, CB inherits CA.
*/

#include <fstream> //printf

//1. Single Inheritance: AA inherits A.
class A
{
public:
	A()
	{
		printf("A()\n");
	}
	~A()
	{
		printf("~A()\n");
	}
};
class AA:public A
{
public:
	AA()
	{
		printf("AA()\n");
	}
	~AA()
	{
		printf("~AA()\n");
	}
};
class AAA :public AA
{
public:
	AAA()
	{
		printf("AAA()\n");
	}
	~AAA()
	{
		printf("~AAA()\n");
	}
};
void SinglInheritance()
{
	printf("\nSingle Inherit\n");
	AAA AAA;
}
// 2.Multiple inheritance : BC inherits BAand BB.
class BA
{
public:
	BA()
	{
		printf("BA()\n");
	}
	~BA()
	{
		printf("~BA()\n");
	}
};
class BB
{
public:
	BB()
	{
		printf("BB()\n");
	}
	~BB()
	{
		printf("~BB()\n");
	}
};
class BC :public BA, public BB
{
public:
	BC()
	{
		printf("BC()\n");
	}
	~BC()
	{
		printf("~BC()\n");
	}
};
void MutipleInheritance()
{
	printf("\nMutiple Inheritance\n");
	BC BC;
}
// 3. Virtul inheritance : CD virtual inherits CBand CC, CC virtual inherits CA, CB virtual inherits CA.
class CA
{
public:
	CA()
	{
		printf("CA()\n");
	}
	~CA()
	{
		printf("~CA()\n");
	}
};
class CB:virtual public CA
{
public:
	CB()
	{
		printf("CB()\n");
	}
	~CB()
	{
		printf("~CB()\n");
	}
};
class CC :virtual public CA
{
public:
	CC()
	{
		printf("CC()\n");
	}
	~CC()
	{
		printf("~CC()\n");
	}
};
class CD :virtual public CB, virtual public CC
{
public:
	CD()
	{
		printf("CD()\n");
	}
	~CD()
	{
		printf("~CD()\n");
	}
};
void VirtualInheriance()
{
	printf("\nVirtual Inheritance\n");
	CD CD;
}
// 4. RepeatInheritance : CD inherits CBand CC, CC inherits CA, CB inherits CA.
class DA
{
public:
	DA()
	{
		printf("DA()\n");
	}
	~DA()
	{
		printf("~DA()\n");
	}
};
class DB : public DA
{
public:
	DB()
	{
		printf("DB()\n");
	}
	~DB()
	{
		printf("~DB()\n");
	}
};
class DC : public DA
{
public:
	DC()
	{
		printf("DC()\n");
	}
	~DC()
	{
		printf("~DC()\n");
	}
};
class DD : public DB, public DC
{
public:
	DD()
	{
		printf("DD()\n");
	}
	~DD()
	{
		printf("~DD()\n");
	}
};
void RepeatInheritance()
{
	printf("\nRepeat Inheritance\n");
	DD DD;
}

int main()
{
	printf("Inherit\n");
	//1. Single Inheritance: AAA inherits AA, AA inherits A.
	SinglInheritance();
	//2. Multiple inheritance: BC inherits BA and BB.
	MutipleInheritance();
	/*3. Virtul inheritance: CD virtual inherits CB and CC
		, CC virtual inherits CA, CB virtual inherits CA.
	*/
	VirtualInheriance();
	//4. RepeatInheritance: CD inherits CB and CC, CC inherits CA, CB inherits CA.
	RepeatInheritance();
	
	
	
	return 0;
}
