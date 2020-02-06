
//AudioProcess 201909031716
#include <fstream> //printf
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")

#define PI 3.14159265359

//Class TextCsvRW
class TextFileRW
{
public:
	//Name
	const char* ExportTextFileName;
	const char* ImportTextFileName;
	//Export
	char OutputBufferChar;
	int OutputBufferInt;
	float OutputBufferFloat;
	//Import
	int* ReadIntBuffer;
	int ReadDateSize;
	//Method
	TextFileRW();
	//Export
	void ExportInitial();
	void CreateExportTextFile();
	void ExportChangeLine();
	void ExportDot();
	void ExportDataChar();
	void ExportDataInt();
	void ExportDataFloat();
	//Import
	void CreateImportTextFile();
	void ReadTxtIntData();
};
//Method
//constructor
TextFileRW::TextFileRW()
{

}

void TextFileRW::ExportInitial()
{

}
//Create Export Text File
void TextFileRW::CreateExportTextFile() //create a file
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::trunc);
	//Check the text file, if it is created fail, show the warming information
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}
	txt_file.close();
}//create a txt file
//Export Data
void TextFileRW::ExportDataChar() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}
	txt_file << OutputBufferChar;
	txt_file.close();
}

void TextFileRW::ExportDataInt() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}
	txt_file << OutputBufferInt;
	txt_file.close();
}

void TextFileRW::ExportDot() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}


	char changeLine[1];
	changeLine[0] = ',';
	txt_file << changeLine[0];

}

void TextFileRW::ExportChangeLine() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}

	//case 1: C
	/**/
	char changeLine[1];
	changeLine[0] = '\n';
	txt_file << changeLine[0];

	//case 2: C++
	/*
	txt_file << endl;
	txt_file.close();
	*/
}

void TextFileRW::ExportDataFloat() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		/*
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		*/
		printf("\nExport_file is opened fail\n");
	}
	txt_file << OutputBufferFloat;
	txt_file.close();
}

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

	//Expand Array
	/*
	for (int i(0); i < DataSize; i++)
	{
		inputArray[-i] = inputArray[i];
		//printf("%f\n", inputArray[-i]);
	}
	exit(0);
	for (int i(0); i < DataSize; i++)
	{
		ConvoArray[-i] = ConvoArray[i];
		//printf("%f\n", inputArray[-i]);
	}*/

	//Convolution Integral
	float dataBuffer(0);
	//float datadubber1(0);
	for (int i(0); i < DataSize; i++)
	{
		for (int j(0); j < i; j++)
		{
			dataBuffer = dataBuffer+ inputArray[j]* ConvoArray[i-j];
			//printf("%f %f %f\n", inputArray[j], ConvoArray[i - j],dataBuffer);
		}
		outputArray[i]= dataBuffer;
		dataBuffer = 0;
	}


	//Show the Result
	/*
	for (int i(0); i < DataSize; i++)
	{
		printf("%f\n", outputArray[i]);
	}*/
}


//
//FFT 2 Radix
/**/
class FFT_2radix
{
public:
	float* re, * im;
	int data_size;
	float samplingRate;
	float* cost, * sint;
	float* output_data_Amplitude;
	float* spectrum_x_axis;
	//
	FFT_2radix();
	void FFT_2radix_initialization();
	void FFT_2radix_algorithm();
	void FFT_2radix_axis();
};
FFT_2radix::FFT_2radix()
{
	data_size = 512;
	re = new float[data_size];
	im = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	output_data_Amplitude = new float[data_size / 2];
}
void FFT_2radix::FFT_2radix_initialization()
{
	delete re, im, cost, sint, output_data_Amplitude;
	re = new float[data_size];
	im = new float[data_size];
	output_data_Amplitude = new float[data_size];
	spectrum_x_axis = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	//printf("%d\n", m);
	float base(0);
	for (int i = 0; i < data_size / 2; i++)
	{
		base = -2 * PI * i / data_size;
		cost[i] = cos(base);
		sint[i] = sin(base);
	}
}
void FFT_2radix::FFT_2radix_algorithm()
{
	//Chech the size of data
	float buf1 = log2(data_size);
	int buf2 = log2(data_size);
	if (buf1 != float(buf2))
	{
		printf("FFT input Size Error \nThe Input Data Size is %d, it must be the n square of 2\n", data_size);
		data_size = pow(2, buf1);
		printf("The Input Data Size will be setting as %d\n", data_size);
		//exit(0);
	}

	int m = log(data_size) / log(2);
	int n = data_size;
	int i = 0;
	int j = 0;
	int k = 0;
	int n1 = 0;
	int n2 = 0;
	int a = 0;

	float cos = 0;
	float sin = 0;
	float t1 = 0;
	float t2 = 0;

	// Bit-reverse
	n2 = n / 2;
	for (i = 1; i < n - 1; i++)
	{

		n1 = n2;
		while (j >= n1)
		{
			j = j - n1;
			n1 = n1 / 2;
		}
		j = j + n1;
		if (i < j)
		{
			t1 = re[i];
			re[i] = re[j];
			re[j] = t1;
			t1 = im[i];
			im[i] = im[j];
			im[j] = t1;
		}
	}

	// FFT
	n1 = 0;
	n2 = 1;

	for (i = 0; i < m; i++)
	{
		n1 = n2;
		n2 = n2 + n2;
		a = 0;

		for (j = 0; j < n1; j++)
		{
			cos = cost[a];
			sin = sint[a];
			for (k = j; k < n; k = k + n2)
			{
				t1 = cos * re[k + n1] - sin * im[k + n1];
				t2 = sin * re[k + n1] + cos * im[k + n1];
				re[k + n1] = re[k] - t1;
				im[k + n1] = im[k] - t2;
				re[k] = re[k] + t1;
				im[k] = im[k] + t2;
			}
			a += 1 << (m - i - 1);
		}
	}
	//To get the absolute value of complex number
	for (int g = 0; g < data_size; g++)
	{
		output_data_Amplitude[g] = sqrt(re[g] * re[g] + im[g] * im[g]) / data_size;
		//printf("%f\n", output_data_Amplitude[g]);
		//printf("%d\n", re[g]);
	}
}
void FFT_2radix::FFT_2radix_axis()
{
	float buf1 = samplingRate / data_size;
	for (int i(0); i < data_size; i++)
	{
		spectrum_x_axis[i] = buf1 * i;
	}
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
		//printf("%f\n", g_Array[i]);
	}

	//
	convo_1.inputArray = x_Array;
	convo_1.ConvoArray = g_Array;
	convo_1.initialize();
	convo_1.ConvolutionIntegralAlgorithm();

	//FFT
	FFT_2radix FFT_X, FFT_Y, FFT_G;
	FFT_X.data_size = convo_1.DataSize;
	FFT_G.data_size = convo_1.DataSize;
	FFT_Y.data_size = convo_1.DataSize;

	FFT_X.FFT_2radix_initialization();
	FFT_G.FFT_2radix_initialization();
	FFT_Y.FFT_2radix_initialization();
	
	FFT_X.re = x_Array;
	FFT_G.re = g_Array;
	FFT_Y.re = convo_1.outputArray;
	for (int i(0); i < FFT_X.data_size; i++)
	{
		FFT_G.im[i] = 0;
		FFT_X.im[i] = 0;
		FFT_Y.im[i] = 0;
	}
	FFT_X.FFT_2radix_algorithm();
	FFT_G.FFT_2radix_algorithm();
	FFT_Y.FFT_2radix_algorithm();
	/*
	printf("\nX\n");
	for (int i(0); i < FFT_X.data_size/2; i++)
	{
		printf("%f\n", FFT_X.output_data_Amplitude[i]);
	}
	
	printf("\nY\n");
	for (int i(0); i < FFT_X.data_size / 2; i++)
	{
		printf("%f\n", FFT_Y.output_data_Amplitude[i]);
	}*/
	printf("\nG\n");
	for (int i(0); i < FFT_X.data_size / 2; i++)
	{
		printf("%f\n", FFT_G.output_data_Amplitude[i]);
	}
	
	

	printf("End\n");
	return 0;
}