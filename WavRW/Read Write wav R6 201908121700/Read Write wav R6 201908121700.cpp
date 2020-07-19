

//Read Write wav R6 201908121700

/**/
#include <fstream> //printf
#include <Windows.h> //read folder, system("PAUSE")
#include<stdio.h>  //fwrite, fread
//#include<stdlib.h> 

#define PI 3.14159




//Read a .wav file
class RW_wav
{
public:
	//Attribute
	const char* wav_name;
	//Read a wav file
	FILE* pFile; //file point
	long wav_data_size;  //The size of file stream
	short* wav_data_buffer; //data buffer, the wav data is 16bits, so using short type
	size_t result;
	//Write a wav file
	char* OutputAudioData;
	const char* ExportWavFileName;

	//Method
	RW_wav();
	//Read wav file
	void read_wav();
	void wavInfo();
	//Write wav file
	void CreateWAV();
	void WriteWAV();
	~RW_wav();
};
//
RW_wav::RW_wav()
{
	//
	//delete wav_name;
	//wav_name = NULL;
	
	//
	//delete wav_data_buffer;
	//wav_data_buffer = NULL;
}
//
void RW_wav::read_wav()
{
	
	pFile = fopen(wav_name, "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}
	//
	fseek(pFile, 0, SEEK_END); //Set the location to the end of file
	// 1 byte Size
	wav_data_size = ftell(pFile); //Returns the end-location value of the position indicator of the stream.
	//printf("wav_data_size=%d\n",wav_data_size);
	// 2 byte Size, Short Size
	wav_data_size = wav_data_size / 2;
	rewind(pFile);

	// allocate memory to contain the whole file:
	wav_data_buffer = (short*)malloc(sizeof(short) * wav_data_size * 2); //set a space for buffer, buffer_size=data_type*data number
	if (wav_data_buffer == NULL) { fputs("Memory error", stderr); } //Check exit(2);

	// copy the file into the buffer:
	result = fread(wav_data_buffer, 1, wav_data_size, pFile);
	//if (result != wav_data_size) { fputs("Reading error", stderr); } //Check exit(3);

	//Stereo Size
	if (wav_data_buffer[11] == 2)
	{
		wav_data_size = wav_data_size / 2;

		for (int i(22); i < wav_data_size; i++)
		{
			wav_data_buffer[i] = (wav_data_buffer[2 * i] + wav_data_buffer[2 * i]) / 2;
		}
	}

	//Release the file point
	fclose(pFile);
	delete pFile;
	//pFile = NULL;
	//
	//delete wav_name;
	//wav_name = NULL;
}
//
void RW_wav::wavInfo()
{
	//Stereo or Mono
	if (wav_data_buffer[11] == 1)
	{
		printf("Channel Number:%d ,Mono Audio\n", wav_data_buffer[11]);
	}
	else
	{
		printf("Channel Number:%d ,Stereo Audio\n", wav_data_buffer[11]);
	}
	//Sampling Rate
	int buffer1(0);
	if (wav_data_buffer[12] < 0) buffer1 = wav_data_buffer[12] + 65536;
	printf("sampling_rate:%d\n", buffer1); //13th is the sampling rate

	//Data Size
	printf("Data Size:%d\n", wav_data_size);
}
//

//
void RW_wav::CreateWAV()
{
	FILE* pFile; //file point
	pFile = fopen(ExportWavFileName, "w"); // if the file is exist, then new one will cover the old.
	if (pFile == NULL) 
	{
		fputs("File error", stderr);
		exit(1);
	}
	fclose(pFile);
}
void RW_wav::WriteWAV()
{
	/*
	char buffer1[] = "Hello World";
	FILE* pFile; //file point
	pFile = fopen(ExportWavFileName, "w");
	fwrite(buffer1, 1, sizeof(buffer1), pFile);
	//fwrite("\r\n", 1, 2, pFile); //change a line
	fclose(pFile);*/

	FILE* fp;
	char str[] = "This is gitbook.net";
	fp = fopen(ExportWavFileName, "w");
	fwrite(str, 1, sizeof(str), fp);
	//fprintf(fp, "sum=%c \n",99);
	fclose(fp);
	

}
//
RW_wav::~RW_wav()
{
	//release wav_name. A breakdown occurs when it is active.
	//delete wav_name;
	//wav_name = NULL;

	//release wav_data_buffer
	delete wav_data_buffer;
	wav_data_buffer = NULL;
}
//
char* itobs(short n)
{
	char* ps = new char[8 * sizeof(short) + 1];
	int size = 8 * sizeof(short);
	int i = size - 1;
	while (i + 1)
	{
		ps[i--] = (1 & n) + '0';
		n >>= 1;
	}
	ps[size] = '\0';
	return ps;
}
	
int main()
{
	//Read a wav file
	RW_wav wav_file_1;
	//Read a Wav file
	wav_file_1.wav_name = "1_halfsecond.wav";
	wav_file_1.read_wav();
	wav_file_1.wavInfo();

	//Write a wav file
	wav_file_1.ExportWavFileName = "WriteWavFile.txt";
	//wav_file_1.CreateWAV();
	wav_file_1.WriteWAV();

	//Show Audio Data
	/*
	for (int i(0); i < wav_file_1.wav_data_size; i++)
	{
		printf("%d\n", wav_
		file_1.wav_data_buffer[i]);
	}*/

	//
	/*
	for (int i(-5); i < 5; i++)
	{
		printf("%d = %s\n", i, itobs(i));
	}*/

	//test
	/**/
	

	system("pause");
	return 0;
}


