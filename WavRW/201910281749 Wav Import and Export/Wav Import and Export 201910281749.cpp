

//Wav Import and Export 201910281749
/*
Read Wav file >> OK
Write Wav File
*/

#include <fstream>
#include <Windows.h> //read folder, system("PAUSE")
//#include <stdio.h>
//#include <stdlib.h>

//
/*
char WavHeader[44] =
{
	82	,
73	,
70	,
70	,
-30	,
12	,
1	,
0	,
87	,
65	,
86	,
69	,
102	,
109	,
116	,
32	,
16	,
0	,
0	,
0	,
1	,
0	,
1	,
0	,
68	,
-84	,
0	,
0	,
-120	,
88	,
1	,
0	,
2	,
0	,
16	,
0	,
100	,
97	,
116	,
97	,
-66	,
12	,
1	,
0

};
*/

class WavRW
{
public:
	//import
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
	WavHeaderForm wavHeader;
	const char* ImportWavFileName;//WavFileName
	short* ImporAudioDataBufferShort; //audioDataBuffer
	long AudioImportDataSizeShort;//AudioDataSize
	//export
	const char* ExportWavFileName;
	char WavHeader[44];
	short* ExportAudioDataBufferShort;
	long ExportAudioDataSizeShort;
	//Method
	WavRW();
	//Import Wav
	void ImportWav();//ReadWav
	void ShowImportAudioInfo(); //ShowWavInformation
	void ShowImortAudioData();
	//Export Wav
	void CreateExportWavFile(); //WriteWav
	void ExportAudioData();
	void ExportWavHeader();//WriteWavHeader
	void SetSampleingRate(short setSamplingRate);
	void SetExportAudioSize();
	
	~WavRW();
};
WavRW::WavRW()
{
	char WavHeader[44] =
	{
		82	,
	73	,
	70	,
	70	,
	-30	,
	12	,
	1	,
	0	,
	87	,
	65	,
	86	,
	69	,
	102	,
	109	,
	116	,
	32	,
	16	,
	0	,
	0	,
	0	,
	1	,
	0	,
	1	,
	0	,
	68	,
	-84	,
	0	,
	0	,
	-120	,
	88	,
	1	,
	0	,
	2	,
	0	,
	16	,
	0	,
	100	,
	97	,
	116	,
	97	,
	-66	,
	12	,
	1	,
	0

	};
}
//Read Wav
void WavRW::ImportWav()
{
	FILE* pFile; //file point

	//Open The wav file
	pFile = fopen(ImportWavFileName, "rb");
	if (pFile == NULL)
	{
		//printf("%d", fileName);
		fputs("File error", stderr);
		exit(1);
	}

	//Read the Header of wav file.
	fread(&wavHeader, 1, sizeof(wavHeader), pFile);


	//Set AudioImportDataSizeShort
	//The Data Size in Short Type is half of the size in one byte.
	AudioImportDataSizeShort = wavHeader.Subchunk2Size / 2;

	//Set Memory for ImporAudioDataBufferShort
	ImporAudioDataBufferShort = new short[AudioImportDataSizeShort];

	//Read audioDataBuffer
	fread(ImporAudioDataBufferShort, sizeof(short), AudioImportDataSizeShort, pFile);

	//Close wav file
	fclose(pFile);

}
void WavRW::ShowImportAudioInfo()
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
		printf("NumChannels \t%d ,Mono\n", wavHeader.NumChannels);
	}
	else
	{
		printf("NumChannels \t%d ,Stereo\n", wavHeader.NumChannels);
	}
	printf("SampleRate \t%d Hz\n", wavHeader.SampleRate);
	printf("ByteRate \t%d\n", wavHeader.ByteRate);
	printf("BlockAlign \t%d\n", wavHeader.BlockAlign);
	printf("BitsPerSample \t%d\n", wavHeader.BitsPerSample);
	printf("blockID \t%c%c%c%c\n", wavHeader.Subchunk2ID[0], wavHeader.Subchunk2ID[1], wavHeader.Subchunk2ID[2], wavHeader.Subchunk2ID[3]);
	printf("blockSize \t%d\n", wavHeader.Subchunk2Size);
	printf("Audio Data Size\n(Short Type) \t%d\n", AudioImportDataSizeShort);
}
void WavRW::ShowImortAudioData()
{
	//Show short type data
	/**/
	for (int i(0); i < 100; i++) //wavHeader.Subchunk2Size / 2
	{
		printf("%d\n", ImporAudioDataBufferShort[i]);
		//printf("i=%d %d\n",i, wavFile1.ImporAudioDataBufferShort[i]);
	}
}
//Export Wav
void WavRW::CreateExportWavFile()
{
	std::ofstream ExportWavFile; 
	ExportWavFile.open(ExportWavFileName, std::ios_base::out | std::ios_base::binary | std::ios::trunc);
	ExportWavFile.close();
}
void WavRW::ExportWavHeader()
{
	//
	std::ofstream ExportWavFile;
	ExportWavFile.open(ExportWavFileName, std::ios::out | std::ios::app | std::ios_base::binary);
	if (!ExportWavFile)
	{
		printf("Export_file is opened fail\n");
	}
	//test check
	for (int i(0); i < 44; i++)
	{
		printf("%d\n", WavHeader[i]);
	}
	exit(0);

	ExportWavFile.write(WavHeader, 44);
	ExportWavFile.close();
}
void WavRW::SetSampleingRate(short setSamplingRate)
{
	WavHeader[24] = setSamplingRate >> 24;
	WavHeader[25] = setSamplingRate >> 16;
	WavHeader[26] = setSamplingRate >> 8;
	WavHeader[27] = setSamplingRate;
}
WavRW::~WavRW()
{
	//free(ImportWavFileName);
	free(ImporAudioDataBufferShort);
}

/*
class testReadWav
{
public:
	const char* WavFileName;
	char* audioDataBuffer;
	short* audioShortDataBuffer;
	long AudioDataSize;
	//Method
	void ReadWav();
	void writeWav();
	void short2char(short inputData);
	~testReadWav();
};
//Read Wav
void testReadWav::ReadWav()
{
	long result(0);
	FILE* pFile; //file point
	pFile = fopen(WavFileName, "rb");
	if (pFile == NULL) { fputs("File error", stderr); exit(1); }
	//
	fseek(pFile, 0, SEEK_END); //Set the location to the end of file
	AudioDataSize = ftell(pFile); //Returns the end-location value of the position indicator of the stream.
	printf("The size of file=%d\n", AudioDataSize);
	rewind(pFile);

	// allocate memory to contain the whole file:
	//audioDataBuffer = (char*)malloc(sizeof(char) * AudioDataSize); //set a space for buffer, buffer_size=data_type*data number
	audioDataBuffer = new char [AudioDataSize];
	//if (audioDataBuffer == NULL) { fputs("Memory error", stderr); exit(2); } //Check
	fread(audioDataBuffer, 1, AudioDataSize, pFile);
	
	//
	//audioShortDataBuffer = new short[AudioDataSize];
	//fread(audioShortDataBuffer, sizeof(short), AudioDataSize/2, pFile);

	//fread(audioDataBuffer, sizeof(short), AudioDataSize, pFile); //reference

	//Release the file point
	fclose(pFile);

}
void testReadWav::writeWav()
{
	std::ofstream outfile("RecordWav.wav", std::ios_base::out | std::ios_base::binary);
	//audioShortDataBuffer
	char* exportCharBuffer = new char[AudioDataSize];
	for (int i(0); i < AudioDataSize/2; i++)
	{
		exportCharBuffer[2*i] = audioShortDataBuffer[i];
		exportCharBuffer[2*i + 1] = audioShortDataBuffer[i]>>8;
		//printf("%d, %d, %d\n", audioShortDataBuffer[i], exportCharBuffer[2 * i], exportCharBuffer[2 * i + 1]);
	}
	outfile.write(exportCharBuffer, AudioDataSize/2);
}
void testReadWav::short2char(short inputData)
{
	short testData(18770);
	char upponData(0), lowerData(0);
	upponData = inputData;
	lowerData = inputData >> 8;
	//printf("%d, %d, %d\n", inputData, upponData, lowerData);

}
testReadWav::~testReadWav()
{
	//free(WavFileName);
	free(audioDataBuffer);
}


//Test
void TestReadWave(const char WavFileName[10])
{
	//Set File Point
	testReadWav wavFile1;
	//Set wav File Name
	wavFile1.WavFileName = WavFileName;
	//Read wav File
	wavFile1.ReadWav();

	//short2char
	//wavFile1.short2char(18770);

	//Write
	//wavFile1.writeWav();


	//Show the audio data
	//short type data
	for (int i(0); i < 44; i++) //wavFile1.AudioDataSize
	{
		//printf("%x\n", wavFile1.audioDataBuffer[i]); 
		printf("%d, %d\n", wavFile1.audioDataBuffer[i]);
		//printf(",%d\n", wavFile1.audioShortDataBuffer[i]);
	}
}
*/
//Import Wav
void ImportWavFile(const char WavFileName[10])
{
	//Set File Point
	WavRW wavFile1;
	//Set wav File Name
	wavFile1.ImportWavFileName = WavFileName;

	//Read wav File
	wavFile1.ImportWav();

	//Show the wav File Header Information
	//wavFile1.ShowImportAudioInfo();
	
	//ShowImortAudioData
	//wavFile1.ShowImortAudioData();


}
void ImportWavFile2(std::string WavFileName)
{
	//Set File Point
	WavRW wavFile1;
	//Set wav File Name
	wavFile1.ImportWavFileName = WavFileName.c_str();
	//Read wav File
	wavFile1.ImportWav();
	//Show the wav File Header Information
	wavFile1.ShowImportAudioInfo();

	//ShowImortAudioData
	wavFile1.ShowImortAudioData();

}
//Export Wav
void ExportWavFile(std::string WavFileName)
{
	WavRW ExportWavFile1;

	//Set Export Name
	ExportWavFile1.ExportWavFileName = WavFileName.c_str();

	//Create Data
	ExportWavFile1.CreateExportWavFile();

	//Set Export Data
	//Export Data
	//Set Header
	//Export Header
	ExportWavFile1.ExportWavHeader();
}
int main()
{
	
	/**/
	const char* ExportWavFileName = "ExportWav.wav"; 
	const char* ImportWavFileName = "ExportWav.wav";
	ExportWavFile(ExportWavFileName);
	ImportWavFile(ImportWavFileName); //input const char
	//ImportWavFile2(ImportWavFileName); //input string
	
	system("pause");
	return 0;
}


