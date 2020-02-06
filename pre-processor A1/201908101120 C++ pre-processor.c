
/*
 
 */
#include<fstream>
#include<stdio.h>

int main()
{
	
    //Example 1
    #define PI 3.14159
    
    //Example 2
    /*
    #define MIN(a,b) (((a)<(b)) ? a : b)
    int i, j;
    i = 100;
    j = 30;
    printf("The Minimum Value is MIN(i, j)：\n");
    //cout <<"The Minimum Value is：" << MIN(i, j) << endl;
    */
     
    //Example 3
    //if HELLO is defined, then do printf and #define
    /*
#ifdef HELLO
    printf("Hello is defined\n");
#define MAX(a,b) (((a)<(b)) ? b : a)
#endif
     */
    
    //Example 4
    /*
#if 0
    printf(" #if 0 means will not be triggle forever\n");
#endif
     */
    
    //Example 5
    /*
    #define MKSTR( x ) #x
    printf("MKSTR(HELLO C++)");
    //cout << MKSTR(HELLO C++) << endl;
    */
    
    //Example 6
    
	return 0;
}
