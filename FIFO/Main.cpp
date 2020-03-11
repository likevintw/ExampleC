// First in, First Out A1

//  g++ ThreadLinux.cpp -o ThreadLinux -lpthread

#include <stdio.h> //printf
#include <pthread.h> // pthread_t
#include <unistd.h> // sleep(100)

struct DataBufferStruct
{
	char Buffer[5];
};

char CatchedData(0);
DataBufferStruct* DataBuffer1= new DataBufferStruct[5];
bool DataFillFlag(0);
char DataBufferPostionFlag(0);

void* GenerateData(void* argu) // 每隔一秒鐘印出一次 George 的函數
{    
	
	for (int i(0), j(0), k(0);; i++,j++)
	{
		if (i > 10)
		{
			i = 0;
		}
		if (j > 4)
		{
			//printf("Buffer is filled out\n");
			DataBufferPostionFlag = k;
			DataFillFlag = 1;
			j = 0;
			k++;
		}
		if(k>4)
		{
			
			k = 0;
		}
		//CatchedData = i;
		DataBuffer1[k].Buffer[j] = i;
		sleep(1);
		//printf("[%d][%d]= %d\n",k,j, DataBuffer1[k].Buffer[j]);
	}
	return NULL;
}

void* StackDataToBuffer(void* argu) // 每隔一秒鐘印出一次 Mary 的函數
{     
	while (1) 
	{
		if (DataFillFlag >0)
		{
			DataFillFlag = 0;
			for (int i(0); i < 5; i++)
			{
				printf("%d ", DataBuffer1[DataBufferPostionFlag].Buffer[i]);
			}
			printf("\n");
			//sleep(7);
		}
	}
	return NULL;
}

int main() 
{    

	printf("First In, First Out, Example\n");
	/*
	One Datum is generated per second.
	Catch 5 data, triggle DataFillFlag.
	Do process for a buffer with 5 data, then waiting for the next DataFillFlag.
	*/
	
	// Define Thread
	pthread_t thread1, thread2;    

	// Set Thread
	pthread_create(&thread1, NULL, &GenerateData, NULL);    // 執行緒 print_george
	pthread_create(&thread2, NULL, &StackDataToBuffer, NULL);    // 執行緒 print_mary
/**/	
	while (1) 
	{     
		//printf("----------------\n");    // Print --- per second
		sleep(1);     
	}

	return 0;
}