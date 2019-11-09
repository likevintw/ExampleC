#include <stdio.h>

int main()
{
	char array[100];

	printf("Enter a string\n");
	scanf("%s", array); //writing with keyboard

	printf("Your string: %s\n", array); 
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
*/
