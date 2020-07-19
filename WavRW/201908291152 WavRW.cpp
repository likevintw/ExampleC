

//Wav Read and Write 201908291152
/*
Read Wav file >> OK
Write Wav File
*/

#include <fstream>
#include <Windows.h> //read folder, system("PAUSE")
//#include <stdio.h>
//#include <stdlib.h>

class WavRW
{
public:
	struct WavHeaderForm
	{
		//WAV Head Fomate
		/* chunk "riff" */
		char ChunkID[4];   /* "RIFF" */
		/* sub-chunk-size */
		uint32_t ChunkSize; /* 36 + Subchunk2Size */
		/* sub-chunk-data */
		char Format[4];    /* "WAVE" */
		//
		/* sub-chunk "fmt" */
		char Subchunk1ID[4];   /* "fmt " */
		/* sub-chunk-size */
		uint32_t Subchunk1Size; /* 16 for PCM */
		/* sub-chunk-data */
		uint16_t AudioFormat;   /* PCM = 1*/
		uint16_t NumChannels;   /* Mono = 1, Stereo = 2, etc. */
		uint32_t SampleRate;    /* 8000, 44100, etc. */
		uint32_t ByteRate;  /* = SampleRate * NumChannels * BitsPerSample/8 */
		uint16_t BlockAlign;    /* = NumChannels * BitsPerSample/8 */
		uint16_t BitsPerSample; /* 8bits, 16bits, etc. */
		//
		/* sub-chunk "data" */
		char Subchunk2ID[4];   /* "data" */
		/* sub-chunk-size */
		uint32_t Subchunk2Size; /* data size */
	};
	const char* WavFileName; 
	WavHeaderForm wavHeader;
	short* audioDataBuffer;
	long AudioDataSize;
	//Method
	void ReadWav();
	void ShowWavInformation();
	~WavRW();
};

void WavRW::ReadWav()
{
	FILE* pFile; //file point

	//Open The wav file
	pFile = fopen(WavFileName, "rb");
	if (pFile == NULL)
	{
		//printf("%d", fileName);
		fputs("File error", stderr);
		exit(1);
	}

	//Read the Header of wav file.
	fread(&wavHeader, 1, sizeof(wavHeader), pFile);

	//Set AudioDataSize
	//The Data Size in Short Type is half of the size in one byte.
	AudioDataSize = wavHeader.Subchunk2Size / 2;

	//Set Memory for audioDataBuffer
	audioDataBuffer = new short[AudioDataSize];

	//Read audioDataBuffer
	fread(audioDataBuffer, sizeof(short), AudioDataSize, pFile);
	
	//Close wav file
	fclose(pFile);
	
}
void WavRW::ShowWavInformation()
{
	printf("ChunkID \t%c%c%c%c\n", wavHeader.ChunkID[0], wavHeader.ChunkID[1], wavHeader.ChunkID[2], wavHeader.ChunkID[3]);
	printf("ChunkSize \t%d\n", wavHeader.ChunkSize);
	printf("Format \t\t%c%c%c%c\n", wavHeader.Format[0], wavHeader.Format[1], wavHeader.Format[2], wavHeader.Format[3]);
	printf("Subchunk1ID \t%c%c%c%c\n", wavHeader.Subchunk1ID[0], wavHeader.Subchunk1ID[1], wavHeader.Subchunk1ID[2], wavHeader.Subchunk1ID[3]);
	printf("Subchunk1Size \t%d\n", wavHeader.Subchunk1Size);
	printf("AudioFormat \t%d\n", wavHeader.AudioFormat);
	//printf("NumChannels \t%d\n", NumChannels);
	if (wavHeader.NumChannels == 1)
	{
		printf("NumChannels \t%d Mono\n", wavHeader.NumChannels);
	}
	else
	{
		printf("NumChannels \t%d Stereo\n", wavHeader.NumChannels);
	}
	printf("SampleRate \t%d Hz\n", wavHeader.SampleRate);
	printf("ByteRate \t%d\n", wavHeader.ByteRate);
	printf("BlockAlign \t%d\n", wavHeader.BlockAlign);
	printf("BitsPerSample \t%d\n", wavHeader.BitsPerSample);
	printf("blockID \t%c%c%c%c\n", wavHeader.Subchunk2ID[0], wavHeader.Subchunk2ID[1], wavHeader.Subchunk2ID[2], wavHeader.Subchunk2ID[3]);
	printf("blockSize \t%d\n", wavHeader.Subchunk2Size);
	printf("Audio Data Size\n(Short Type) \t%d\n", AudioDataSize);
}
WavRW::~WavRW()
{
	//free(WavFileName);
	free(audioDataBuffer);
}

void ReadWavFile(const char WavFileName[10])
{
	//Set File Point
	WavRW wavFile1;
	//Set wav File Name
	wavFile1.WavFileName = WavFileName;
	//Read wav File
	wavFile1.ReadWav();
	//Show the wav File Header Information
	wavFile1.ShowWavInformation();

	//Show the audio data
	/*
	for (int i(0); i < wavFile1.wavHeader.Subchunk2Size/2; i++)
	{
		printf("%d\n", wavFile1.audioDataBuffer[i]);
		//printf("i=%d %d\n",i, wavFile1.audioDataBuffer[i]);
	}*/
	
}
void ReadWavFile2(std::string WavFileName)
{
	//Set File Point
	WavRW wavFile1;
	//Set wav File Name
	wavFile1.WavFileName = WavFileName.c_str();
	//Read wav File
	wavFile1.ReadWav();
	//Show the wav File Header Information
	wavFile1.ShowWavInformation();

	//Show the audio data
	/*
	for (int i(0); i < wavFile1.wavHeader.Subchunk2Size/2; i++)
	{
		printf("%d\n", wavFile1.audioDataBuffer[i]);
		//printf("i=%d %d\n",i, wavFile1.audioDataBuffer[i]);
	}*/

}

int main()
{
	const char* WavFileName = "1_halfsecond.wav";
	ReadWavFile(WavFileName); //input const char
	//ReadWavFile2(WavFileName); //input string
	system("pause");
	return 0;
}


