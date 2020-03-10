
// Operator Overloading ReferenceConter A1 
/*
201912191128 A1 Reference
201912191412 A2 
*/
#include <iostream>

class SecretData
{
public:
	int Index;
	int ReferenceNumber;
	SecretData();
	void operator=(SecretData& point);
};
SecretData::SecretData()
{
	Index = 0;
	ReferenceNumber = 0;
}
/**/
void SecretData::operator=(SecretData& point)
{
	ReferenceNumber--; //left of =,--
	point.ReferenceNumber++; //right of =, ++
}


int main() 
{
	
	printf("Referece Counter Example\n");
	SecretData a, b;
	a.Index= 321;
	b = a;
	//b.Index = 123;
	printf("a.Index= %d\n", a.Index);
	printf("b.Index= %d\n", b.Index);


	printf("a.Index= %d\n", &a.Index);
	printf("b.Index= %d\n", &b.Index);

	printf("a.ReferenceNumber= %d\n", a.ReferenceNumber);
	printf("b.ReferenceNumber= %d\n", b.ReferenceNumber);
	
	return 0;
}