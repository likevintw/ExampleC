//Bits Reverse A2
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
int BitsReverse(int inputData, int Size)
{
    int outputData;
    outputData=0;
    Size=Log2(Size);
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

//
void BitsReverseExample()
{
    int dataSize;
    dataSize=16;
    for(int i(0);i<dataSize;i++)
    {
        printf("input[%d]=%d\n",i,BitsReverse(i,dataSize));
    }
}

int main()
{
    BitsReverseExample();
	return 0;
}
