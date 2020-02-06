//
//Reference from 
//http://edisonx.pixnet.net/blog/post/52113788-%5Bc%5D-%E8%A8%88%E6%99%82%E5%99%A8%E6%95%B4%E7%90%86

#include <windows.h> //Sleep()
#include <stdio.h> //printf
#include <time.h>

int main()
{
	clock_t t1, t2;
	t1 = clock();  //Time of Start
	Sleep(1234);
	t2 = clock();  //Time of End
	printf("%lf\n Second", (t2 - t1) / (double)(CLOCKS_PER_SEC));
	return 0;
}
