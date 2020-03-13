// Printf A2
#include <stdio.h>

// Printf and scanf
void PrintfScanf()
{
	char KeyinString[20];

	printf("Enter a string\n");

	int KeyinReturn(0);
	if (scanf("%s", KeyinString)) // if keyining from keyboard is seccessfully.
	{
		// Show the keyined String
		printf("Your string: %s\n", KeyinString);
	}
}

// Printf Type
/*

Character
%c : 字元,  char c;
%C : 字元,  char c;
%s : 字元陣列, char buffer[MAX_PATH];
%S : 字元陣列(Unicode), wchar buffer[MAX_PATH];
[註] %C / %S 並未被收在標準函式庫裡，屬 MSVC 特殊支援。


integer
%d, %i : 10進制整數  , int x; [lemma]

unsigned
%o : 8進制無號數,  unsigned int x;
%u : 10進制無號數, unsigned int x;
%x, %X : 16進制無號數, 小寫x輸出為"abcdef", 大寫 X 輸出為 "ABCDEF", unsigned x;
%lld, %I64d : long long int, __int64 輸出型態(註：vc6.0 下只有 __int64，沒有long long int)
%llu, %I64u : unsigned long long int  輸出型態

address
%p : 變數位置。 ex:
int a=0, printf("%p", &a);  即 printf("%08x", &a);
%n : 輸出至緩衝區之長度, ex:
char str[]="test", int len, printf("%s%n", a, &len);
*/
void TypePresentation()
{
	// Formula
	/*
	\n
	\t
	*/
	printf("\nFormula\n");
	printf("Hi\tWorld\n");
	printf("Hello\tWorld\n");

	// Float Type
	/*
	Float
	%e : 浮點數使用科學符號表示之,指數將帶正負號, float x,doubley;
	%E : 浮點數使用科學符號表示之,指數將帶正負號, float x,doubley;
	%f : 單精度浮點數(預設輸出精度6位), float x;(註 : 對 printf 而言, %f/%lf 可適用於 double / float)
	%lf : 倍精度浮點數(預設輸出精度6位), double x;
	%llf: 雙倍精度浮點數(預設輸出精度6位), long double x;
	%LF : 雙倍精度浮點數(預設輸出精度6位), long double x;
	%g	: 由系統決定是否採科學符號表示。 
	%G	: 由系統決定是否採科學符號表示。
	*/
	float floatBuffer(3.14159265359);
	printf("\nfloat floatBuffer(3.14159265359);\n");
	printf("%%f\t %f\n", floatBuffer);			// Float type
	printf("%%.2f\t %.2f\n", floatBuffer);		// second digit
	printf("%%e\t%e\n", floatBuffer);			// Scientific Notation
	printf("%%E\t%E\n", floatBuffer);			// Scientific Notation
	printf("%%g\t%g\n", floatBuffer);			// Presenting the shortest type between %f and %e
	printf("%%G\t%G\n", floatBuffer);			// Presenting the shortest type between %f and %e
	printf("%%10.5\t%10.5f\n", floatBuffer);	// 10 characters lenght for printer, and the accurate to the fifth digit after the decimal point

	// Double Type
	double doubleBuffer(3.14159265359);
	printf("\ndouble doubleBuffer(3.14159265359)\n");
	printf("%%f\t%f\n", doubleBuffer);
	printf("%%lf\t%lf\n", doubleBuffer);

	// Long Double
	long double longDoubleBuffer(3.14159265359);
	printf("\nlong double longDoubleBuffer(3.14159265359);\n");
	printf("%%LF\t%LF\n", longDoubleBuffer);

	//Binary
	char CharBuffer(98),s(0);
	printf("\nchar CharBuffer(%d);\n", CharBuffer);
	printf("%%c character\t%c\n", CharBuffer);
	printf("%%o Octal\t%o\n", CharBuffer);
	printf("%%d Decimal\t%d\n", CharBuffer);
	printf("%%x Hexadecimal\t%x\n", CharBuffer);

	//unsigned
	char testUnsiged(-98);
	printf("\nchar testUnsiged(-98);\n");
	printf("%%u \t%u\n", testUnsiged);
	testUnsiged = 98;
	printf("char testUnsiged(98);\n");
	printf("%%u \t%u\n", testUnsiged);

}

int main()
{
	/*
	PrintfScanf();
	*/
	TypePresentation();

	return 0;
}

/*

%c			以字元方式輸出
%C			以字元方式輸出
%s  		字元陣列, char buffer[MAX_PATH];
%S  		字元陣列, char buffer[MAX_PATH];
[註] %C / %S 並未被收在標準函式庫裡，屬 MSVC 特殊支援。
%d			10進制整數  , int x; [lemma]
%ld			Long 10進制整數  , int x; [lemma]
%i			10進制整數  , int x; [lemma]
%u			無號整數輸出
%lu			Long 無號整數輸出
%f			浮點數輸出
%lf			Long 浮點數輸出
%LF			Long 浮點數輸出
%e			使用科學記號顯示浮點數
%E			使用科學記號顯示浮點數
%g			浮點數輸出，取 %f 或 %e（%f 或 %E），看哪個表示精簡
%G			浮點數輸出，取 %f 或 %e（%f 或 %E），看哪個表示精簡
%%			顯示 %
%s			字串輸出
%lu			long unsigned 型態的整數
%p			Address
%o :		8進制無號數,  unsigned int x;
%x, %X :	16進制無號數, 小寫x輸出為"abcdef", 大寫 X 輸出為 "ABCDEF", unsigned x;
%u :		10進制無號數, unsigned int x;
%lld,%I64d	long long int, __int64 輸出型態(註：vc6.0 下只有 __int64，沒有long long int)
%llu,%I64u	unsigned long long int  輸出型態%n : 輸出至緩衝區之長度, ex:
%n 			輸出至緩衝區之長度, ex:char str[]="test", int len, printf("%s%n", a, &len);
%zu

*/
