
// Operator Overloading ComplexNumber A2
/*
201912191128 A1 Reference
201912191412 A2 
*/
#include <iostream>

class Complex
{
public:
	float re, im;
	Complex();
	Complex(float x, float y);
	Complex operator+(Complex&);
	Complex operator-(Complex&);
	Complex operator*(Complex&);
	Complex operator/(Complex&);
};
Complex::Complex()
{
	re = 0;
	im = 0;
}
Complex::Complex(float x, float y)
{
	re = x;
	im = y;
}
Complex Complex::operator+(Complex& c)
{
	Complex complexBuffer(re + c.re, im + c.im);
	return complexBuffer;
}
Complex Complex::operator-(Complex& c)
{
	Complex complexBuffer(re - c.re, im - c.im);
	return complexBuffer;
}
Complex Complex::operator*(Complex& c)
{
	Complex complexBuffer(re * c.re, im * c.im);
	return complexBuffer;
}
Complex Complex::operator/(Complex& c)
{
	
	if (c.re==0)
	{
		printf("The Real Part Denominator is Zero\n");
		Complex complexBuffer(0, 0);
		return complexBuffer;
	}
	if (c.im == 0)
	{
		printf("The Image Part Denominator is Zero\n");
		Complex complexBuffer(0, 0);
		return complexBuffer;
	}
	Complex complexBuffer(re / c.re, im / c.im);
	return complexBuffer;
}
int main() 
{
	
	printf("Operator Overloading Example\n");
	Complex c1(7,8), c2(0,5),c3;
	printf("c1=(%f,%f)\n", c1.re, c1.im);
	printf("c2=(%f,%f)\n", c2.re, c2.im);
	//
	printf("\n");
	printf("c3 = c1 + c2\n");
	c3 = c1 + c2;
	printf("c3=(%f,%f)\n", c3.re, c3.im);
	//
	printf("\n");
	printf("c3 = c1 - c2\n");
	c3 = c1 - c2;
	printf("c3=(%f,%f)\n", c3.re, c3.im);
	//
	printf("\n");
	printf("c3 = c1 * c2\n");
	c3 = c1 * c2;
	printf("c3=(%f,%f)\n", c3.re, c3.im);
	//
	printf("\n");
	printf("c3 = c1 / c2\n");
	c3 = c1 / c2;
	printf("c3=(%f,%f)\n", c3.re, c3.im);

	return 0;
}