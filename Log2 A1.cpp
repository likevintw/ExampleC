//Log2 A1
#include <stdio.h> //printf


//
int Log2(int inputDataLog2)
{
    int OutputData(0);
    // Show the Size of integer type, 4
    //printf("size %lu\n",sizeof(inputDataLog2));
    for(int i(0);i<sizeof(inputDataLog2)*8;i++)
    {
        if(inputDataLog2%2==1)
        {
            //printf("%d\n",i);
            OutputData=i;
        }
        inputDataLog2=inputDataLog2>>1;
    }
    return OutputData;
}



//
void Log2Example()
{
    for(int i(0);i<65;i++)
    {
        printf("input[%d]=%d\n",i,Log2(i));
    }
}


int main()
{
    Log2Example();
	return 0;
}
