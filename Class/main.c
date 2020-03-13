

#include <stdio.h> // cout, cin
#include <fstream> //printf
#include <string>

using namespace std;

// single inheritance
// structor and de-structor, A() and ~A()
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
class AA :public A
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
	printf("\nSingle Inherit()\n");
	printf("class AA :public A\n");
	printf("class AAA :public AA\n");
	AAA AAA;
}

//Structor And Destructrue
void StructorAndDestructrue(void)
{
	printf("\nStructorAndDestructrue()\n");
	printf("class AA :public A\n");
	printf("class AAA :public AA\n");
	AAA AAA;
}

// Multiple inheritance : BC inherits BA and BB.
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
	printf("\nMutiple Inheritance()\n");
	printf("class BC :public BA, public BB\n");
	BC BC;
}

// Virtul inheritance : CD virtual inherits CBand CC, CC virtual inherits CA, CB virtual inherits CA.
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
class CB :virtual public CA
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
	printf("\nVirtual Inheritance()\n");
	printf("class CB :virtual public CA\n");
	printf("class CC :virtual public CA\n");
	printf("class CD :virtual public CB, virtual public CC\n");
	CD CD;
}

// RepeatInheritance: CD inherits CBand CC, CC inherits CA, CB inherits CA.
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
	printf("\nRepeat Inheritance()\n");
	printf("class DB : public DA\n");
	printf("class DC : public DA\n");
	printf("class DD : public DB, public DC\n");
	DD DD;
}

// Attributes and Methods
class Car
{
public:
	//Attribute
	std::string CarColor;
	int CarVolume;
	string CarName;
	//Method
	Car();
	void ShowCarVolume();
	void ShowCarColor();
};
Car::Car()
{
	CarColor = "undefined";
	CarName = "undefined";
	CarVolume = -1;
}
void Car::ShowCarColor()
{
	printf("The Car %s Color is %s\n", CarName.c_str(),CarColor.c_str());
}
void Car::ShowCarVolume()
{
	if (CarVolume < 0)
	{
		printf("The Car %s Volume is undefined\n", CarName.c_str());
	}
	else
	{
		printf("The Car %s Volume is %dcc\n", CarName.c_str(), this->CarVolume);
	}
	
}
void AttributeAndMethod(void)
{
	printf("\nAttributeAndMethod()\n");
	// Car is a class.
	// carA and carB are Instance or Object.
	Car carA, carB;
	carA.ShowCarColor();
	carA.ShowCarVolume();
	carA.CarName = "A";
	carA.CarColor = "Red";
	carA.CarVolume = 1600;
	carA.ShowCarColor();
	carA.ShowCarVolume();
	printf("\n");
	carB.ShowCarColor();
	carB.ShowCarVolume();
	carB.CarName = "B";
	carB.CarColor = "Blue";
	carB.CarVolume = 2400;
	carB.ShowCarColor();
	carB.ShowCarVolume();
}

// Encapsulation 
class StudentInfo
{
private:
	string StudentName;
public:
	StudentInfo();
	void ShowStudentName();
	void EditStudentName(string input);
};
StudentInfo::StudentInfo()
{
	StudentName = "Undefined";
}
void StudentInfo::ShowStudentName()
{
	printf("Student Name is %s\n", StudentName.c_str());
}
void StudentInfo::EditStudentName(string input)
{
	StudentName = input;
	printf("Student Name is updated\n");
}
void Example_Encapsulation(void)
{
	// the attribute is privated
	printf("\nExample_Encapsulation\n");
	StudentInfo A;
	A.ShowStudentName();
	//A.StudentName = "John"; // Error, private type
	A.EditStudentName("John");
	A.ShowStudentName();
}

// Example_polymorphism (), Dynamic polymorphism
// Polymorphism, PA mothod must be set virtual
class PA
{
public:
	virtual void Show() { printf("PA\n"); } // Must be virtual
};
class PB: public PA
{
public:
	void Show() { printf("PB\n"); }
};
class PC : public PA
{
public:
	void Show() { printf("PC\n"); }
};
class PD : public PB, public PC
{
public:
	void Show() { printf("PD\n"); }
};
void Example_Polymorphism(void)
{
	PA* Poly;
	PA A;
	PB B;
	PC C;
	PD D;
	Poly = &A;
	Poly->Show();
	Poly = &B;	
	Poly->Show();
	Poly = &C;
	Poly->Show();
	//Poly = &D; // Error
	//Poly->Show();

}

// Example_Overload(), Static polymorphism, Unfinished
class DataType
{
public:
	void ShowDataType(int inputData);
	void ShowDataType(float inputData);
	void ShowDataType(char inputData);
};
void DataType::ShowDataType(int inputData)
{
	printf("Data Type is Interger\n");
}
void DataType::ShowDataType(float inputData)
{
	printf("Data Type is Float\n");
}
void DataType::ShowDataType(char inputData)
{
	printf("Data Type is Character\n");
}
void Example_Overload(void)
{
	printf("\nExample_Overload()\n");
	DataType test;
	char charData(55);
	float floatData(55);
	int intData(55);
	test.ShowDataType(charData);
	test.ShowDataType(floatData);
	test.ShowDataType(intData);
}

// Example_Override()
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
void Example_Override(void)
{
	// Override Example
	printf("\nExample_Override()\n");
	//
	Mandarin helloA;
	helloA.sayHello();
	//
	English helloB;
	helloB.sayHello();
}

int main()
{
	/*
	SinglInheritance();
	StructorAndDestructrue();
	MutipleInheritance();
	VirtualInheriance();
	RepeatInheritance();
	AttributeAndMethod();
	Example_Encapsulation();
	Example_Polymorphism();
	Example_Overload();
	Example_Override();
	*/
	StructorAndDestructrue();
	return 0;
}
