// Printf A2
#include <stdio.h>


// Input and Output
void PrintAndScan()
{
	char KeyinString[100];

	/**/
	// Input and Output
	printf("Enter a string\n");
	// Keyin Data from keyboard
	int KeyinReturn(0);
	if (scanf("%s", KeyinString)) // if keyining from keyboard is seccessfully.
	{
		// Show the keyined String
		printf("Your string: %s\n", KeyinString);
	}
}
// Printf Type
void TypePresentation()
{
	// Float Type
	float floatBuffer(3.14159265359);
	printf("%f\n", floatBuffer);			// Float type
	printf("%.2f\n", floatBuffer);			// Accurate to the second digit after the decimal point
	printf("%e\n", floatBuffer);			// Presenting with Scientific Notation, as called as Standard Form.
	printf("%g\n", floatBuffer);			// Presenting the shortest type between %f and %e
	printf("%10.5f\n", floatBuffer);		// 10 characters lenght for printer, and the accurate to the fifth digit after the decimal point

	// Double Type
	double doubleBuffer(3.14159265359);
	printf("%lf\n", doubleBuffer);			//%LF
}
int main()
{
	char KeyinString[100];

	/**/
	// Input and Output
	printf("Enter a string\n");
	// Keyin Data from keyboard
	int KeyinReturn(0);
	if (scanf("%s", KeyinString)) // if keyining from keyboard is seccessfully.
	{
		// Show the keyined String
		printf("Your string: %s\n", KeyinString);
	}
	

	// Printf Type
/*
	// Float Type
	float floatBuffer(3.14159265359);
	printf("%f\n", floatBuffer);			// Float type
	printf("%.2f\n", floatBuffer);			// Accurate to the second digit after the decimal point
	printf("%e\n", floatBuffer);			// Presenting with Scientific Notation, as called as Standard Form.
	printf("%g\n", floatBuffer);			// Presenting the shortest type between %f and %e
	printf("%10.5f\n", floatBuffer);		// 10 characters lenght for printer, and the accurate to the fifth digit after the decimal point
	
	// Double Type
	double doubleBuffer(3.14159265359);
	printf("%lf\n", doubleBuffer);			//%LF
*/
	return 0;
}

/*
vector vecImages: printf("vecImages: %s \n", vecImages[i].c_str());
size_t: %zu

Reference http://edisonx.pixnet.net/blog/post/35305668-%5Bc%5D-printf-%E5%BC%95%E6%95%B8%E8%AA%AA%E6%98%8E
%c, %C : 字元,  char c;
%s : 字元陣列, char buffer[MAX_PATH];
%S : 字元陣列(Unicode), wchar buffer[MAX_PATH];
[註] %C / %S 並未被收在標準函式庫裡，屬 MSVC 特殊支援。

整數
%d, %i : 10進制整數  , int x; [lemma] 
%u : 10進制無號數, unsigned int x;
%o : 8進制無號數,  unsigned int x;
%x, %X : 16進制無號數, 小寫x輸出為"abcdef", 大寫 X 輸出為 "ABCDEF", unsigned x;
%lld, %I64d : long long int, __int64 輸出型態(註：vc6.0 下只有 __int64，沒有long long int)
%llu, %I64u : unsigned long long int  輸出型態

浮點數
%e, %E : 浮點數使用科學符號表示之,指數將帶正負號, float x,doubley;
%f : 單精度浮點數(預設輸出精度6位), float x;(註 : 對 printf 而言, %f/%lf 可適用於 double / float)
%lf : 倍精度浮點數(預設輸出精度6位), double x;
%llf, %LF : 雙倍精度浮點數(預設輸出精度6位), long double x;
%g, %G : 由系統決定是否採科學符號表示。

特殊 
%p : 變數位置。 ex:
int a=0, printf("%p", &a);  即 printf("%08x", &a);
%n : 輸出至緩衝區之長度, ex:
char str[]="test", int len, printf("%s%n", a, &len);
輸出4bytes,len = 4

%c	以字元方式輸出
%d	10 進位整數輸出
%o	以 8 進位整數方式輸出
%u	無號整數輸出
%x, %X	將整數以 16 進位方式輸出
%f	浮點數輸出
%e, %E	使用科學記號顯示浮點數
%g, %G	浮點數輸出，取 %f 或 %e（%f 或 %E），看哪個表示精簡
%%	顯示 %
%s	字串輸出
%lu	long unsigned 型態的整數
%p	指標型態

*/
