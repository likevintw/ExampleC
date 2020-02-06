
//201909051349 Convolution Integral 
#include <fstream> //printf
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")

#define PI 3.14159265359


//ConvolutionIntegralClass
class ConvolutionIntegralClass
{
public:
	float* inputArray, * ConvoArray, * outputArray;
	int DataSize;
	//Method
	ConvolutionIntegralClass();
	void initialize();
	void ConvolutionIntegralAlgorithm();
};
ConvolutionIntegralClass::ConvolutionIntegralClass()
{
	DataSize = 1;
}
void ConvolutionIntegralClass::initialize()
{
	//inputArray = new float[DataSize];
	//ConvoArray = new float[DataSize*2];
	outputArray = new float[DataSize];
}
void ConvolutionIntegralClass::ConvolutionIntegralAlgorithm()
{
	//Convolution Integral
	float dataBuffer(0);
	//float datadubber1(0);
	for (int i(0); i < DataSize; i++)
	{
		for (int j(0); j < i; j++)
		{
			dataBuffer = dataBuffer+ inputArray[j]* ConvoArray[i-j];
			//printf("%f %f %f\n", inputArray[j], ConvoArray[i - j], dataBuffer);
		}
		outputArray[i]= dataBuffer;
		dataBuffer = 0;
	}


	//Show the Result
	/*
	for (int i(0); i < DataSize; i++)
	{
		//printf("%f %f %f\n", inputArray[i], ConvoArray[i], outputArray[i]);
		printf("%f\n", outputArray[i]);
	}*/
}



int main()
{
	printf("Convolution Integral\n");
	
	//ConvolutionIntegralClass
	ConvolutionIntegralClass convo_1;
	convo_1.DataSize = 512;


	//Set Array
	float* x_Array, *g_Array;
	x_Array = new float[convo_1.DataSize];
	g_Array = new float[convo_1.DataSize];

	//Set x
	float base(0);
	for (int i(0); i < convo_1.DataSize; i++)
	{
		base = 2 * PI * i / convo_1.DataSize;
		x_Array[i]=cos(base)+cos(100*base); //cost+cos10t
		//printf("%f\n", g_Array[i]);
	}

	//Set g
	float Wc(220);
	for (int i(0); i < convo_1.DataSize; i++)
	{
		//Case1
		/**/
		if (i == 0)
		{
			g_Array[i] = Wc / PI;
		}
		else
		{
			base = 2 * PI * i / convo_1.DataSize;
			base = base * Wc;
			g_Array[i] = sin(base)/(PI*i);

		}

		//Case2 g[t]=t
		/*
		g_Array[i] = i;*/

		//Show Data
		//printf("%f\n", g_Array[i]);
	}

	//Do Convolution Integral
	convo_1.inputArray = x_Array;
	convo_1.ConvoArray = g_Array;
	convo_1.initialize();
	convo_1.ConvolutionIntegralAlgorithm();

	//Show Time Domain Data
	//Show x time domain
	/*
	for (int i(0); i < convo_1.DataSize; i++)
	{
		printf("%f\n", convo_1.inputArray[i]);
	}
	printf("\n \n");
	//Show g time domain
	for (int i(0); i < convo_1.DataSize; i++)
	{
		printf("%f\n", convo_1.ConvoArray[i]);
	}
	//Show Y time domain
	
	for (int i(0); i < convo_1.DataSize; i++)
	{
		printf("%f\n", convo_1.outputArray[i]/14000);
	}*/
	
	printf("End\n");
	return 0;
}