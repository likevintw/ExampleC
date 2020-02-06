//BitReverseA1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int BitReverse(int inputData, int Size)
{
    int outputData;
    outputData=0;
    Size=log2(Size);
    for(int i(0);i<Size;i++)
    {
        //printf("%d",inputData%2); //Show Reversed Bite
        outputData=outputData+inputData%2;
        if(i==Size-1) break;
        inputData=inputData>>1;
        outputData=outputData<<1;
    }
    //printf("\n"); //Show Reversed Bite
    return outputData;
}

int main()
{
    int dataSize;
    dataSize=16;
    for(int i(0);i<dataSize;i++)
    {
        printf("input[%d]=%d\n",i,BitReverse(i,dataSize));
    }
	return 0;
}
