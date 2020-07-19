
/*
wav file R/W R4 20190516_1432
*/

#include <stdio.h> //fopen, fseek, ftell
#include <stdlib.h> //malloc, exit


class RW_wav
{
public:
	const char* wav_name; 
	FILE* pFile; //file point
	long wav_data_size;  //The size of file stream
	long short_data_size; //The size of buffer with short type (Important)
	short* wav_data_buffer; //data buffer, the wav data is 16bits, so using short type
	size_t result;
	RW_wav()
	{
		wav_data_size = 100;
		wav_data_buffer = (short*)malloc(sizeof(short) * wav_data_size);
	}
	void read_wav()
	{
		pFile = fopen(wav_name, "rb");
		if (pFile == NULL) { fputs("File error", stderr); exit(1); }
		//
		fseek(pFile, 0, SEEK_END); //Set the location to the end of file
		wav_data_size = ftell(pFile); //Returns the end-location value of the position indicator of the stream.
		short_data_size = wav_data_size / 2;
		printf("The size of file=%d\n", wav_data_size);
		rewind(pFile);

		// allocate memory to contain the whole file:
		wav_data_buffer = (short*)malloc(sizeof(short) * wav_data_size); //set a space for buffer, buffer_size=data_type*data number
		if (wav_data_buffer == NULL) { fputs("Memory error", stderr); exit(2); } //Check

		// copy the file into the buffer:
		result = fread(wav_data_buffer, 1, wav_data_size, pFile);
		if (result != wav_data_size) { fputs("Reading error", stderr); exit(3); } //Check


		//Release the file point
		fclose(pFile);
	}
	~RW_wav()
	{
		delete wav_data_buffer;
		wav_data_buffer = NULL;
	}
};

int main() 
{
	RW_wav wav_file;
	wav_file.wav_name = "bosch2.wav"; //define the wav file name
	wav_file.read_wav(); //Read the wav file

	//Check, show the data in the buffer
	/**/
	for (int i(0); i < 30; i++)
	{
		printf("%d\n", wav_file.wav_data_buffer[i]);
	}
		
	
	printf("Finished\n");

	// terminate
	system("pause");
	return 0;
}


/*
檔案前44(或46)位元組放置檔頭(header)，各自有特殊意義
並非聲音檔案，處理時必須避開
換算16bits的資料型態，前面22/23個資訊為檔頭
*/