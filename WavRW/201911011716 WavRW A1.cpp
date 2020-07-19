

// 201911011716 WavRW_A1
/*
Read Wav file >> OK
Write Wav File
*/

#include <fstream>
#include <Windows.h> //read folder, system("PAUSE")
//#include <stdio.h>
//#include <stdlib.h>
#include<math.h>


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
	short* ImporAudioDataBufferShort; //ImporAudioDataBufferShort ImportAudioDataSizeShort
	long ImportAudioDataSizeShort;//AudioImportDataSizeShort
	//export
	const char* ExportWavFileName;
	char* ExportWavHeaderBuffer;
	char* ExportAudioDataBufferChar;//ExportAudioDataBufferChar ExportAudioDataSizeChar
	int ExportAudioDataSizeChar;
	int ExportSamplingRate;
	//Method
	WavRW();
	//Import Wav
	void ImportWav();//ReadWav
	void ShowImportAudioInfo(); //ShowWavInformation
	void ShowImortAudioData();
	//Export Wav
	void CreateExportWavFile(); //WriteWav
	void SetAudioData(int inpuFre);
	void ExportAudioData();
	void ExportWavHeader();//WriteWavHeader
	void SetSampleingRate(int setSamplingRate);
	void SetExportAudioSize(int inputData);

	~WavRW();
};
WavRW::WavRW()
{
	ExportWavHeaderBuffer = new char[44];
	char DataBuffer[44] =
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
	//Test
	/**/
	//printf("WavRW()\n");
	for (int i(0); i < 44; i++)
	{
		ExportWavHeaderBuffer[i] = DataBuffer[i];
		//printf("%d\n", ExportWavHeaderBuffer[i]);
	}

	//ExportSamplingRate
	ExportSamplingRate = 16000; //Default
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

	//ShowShowImportAudioInfo
	ShowImportAudioInfo();

	//test
	exit(0);

	//Set ImportAudioDataSizeShort
	//The Data Size in Short Type is half of the size in one byte.
	ImportAudioDataSizeShort = wavHeader.Subchunk2Size / 2;

	//Set Memory for ImporAudioDataBufferShort
	ImporAudioDataBufferShort = new short[ImportAudioDataSizeShort];

	//Read audioDataBuffer
	fread(ImporAudioDataBufferShort, sizeof(short), ImportAudioDataSizeShort, pFile);

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
	printf("ByteRate \t%d bits/s\n", wavHeader.ByteRate);
	printf("BlockAlign \t%d\n", wavHeader.BlockAlign);
	printf("BitsPerSample \t%d\n", wavHeader.BitsPerSample);
	printf("blockID \t%c%c%c%c\n", wavHeader.Subchunk2ID[0], wavHeader.Subchunk2ID[1], wavHeader.Subchunk2ID[2], wavHeader.Subchunk2ID[3]);
	printf("blockSize \t%d\n", wavHeader.Subchunk2Size);
	printf("Audio Data Size\n(Short Type) \t%d\n", ImportAudioDataSizeShort);
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
void WavRW::SetAudioData(int inpuFre)
{

}
void WavRW::ExportAudioData()
{
	std::ofstream ExportWavFile;
	ExportWavFile.open(ExportWavFileName, std::ios::out | std::ios::app | std::ios_base::binary);
	if (!ExportWavFile)
	{
		printf("Export_file is opened fail\n");
	}
	//test check
	/*
	printf("ExportAudioDataBufferChar()\n");
	for (int i(0); i < 44; i++)
	{
		printf("%d\n", ExportAudioDataBufferChar[i]);
	}*/


	ExportWavFile.write(ExportAudioDataBufferChar, ExportAudioDataSizeChar);
	ExportWavFile.close();
}
void WavRW::ExportWavHeader()
{
	//
	std::ofstream ExportWavFile;
	ExportWavFile.open(ExportWavFileName, std::ios::out | std::ios::ate | std::ios_base::binary);
	if (!ExportWavFile)
	{
		printf("Export_file is opened fail\n");
	}
	//test check
	/*
	printf("ExportWavHeader()\n");
	for (int i(0); i < 44; i++)
	{
		printf("%d\n", ExportWavHeaderBuffer[i]);
	}*/


	ExportWavFile.write(ExportWavHeaderBuffer, 44);
	ExportWavFile.close();
	//exit(0);
}
void WavRW::SetSampleingRate(int inputData)
{
	//ExportSamplingRate
	ExportSamplingRate = inputData;
	//
	ExportWavHeaderBuffer[27] = inputData >> 24;
	ExportWavHeaderBuffer[26] = inputData >> 16;
	ExportWavHeaderBuffer[25] = inputData >> 8;
	ExportWavHeaderBuffer[24] = inputData;
	//
	inputData = inputData * 2; //16 bits
	//
	ExportWavHeaderBuffer[31] = inputData >> 24;
	ExportWavHeaderBuffer[30] = inputData >> 16;
	ExportWavHeaderBuffer[29] = inputData >> 8;
	ExportWavHeaderBuffer[28] = inputData;
}
void WavRW::SetExportAudioSize(int inputData)
{
	ExportWavHeaderBuffer[43] = inputData >> 24;
	ExportWavHeaderBuffer[42] = inputData >> 16;
	ExportWavHeaderBuffer[41] = inputData >> 8;
	ExportWavHeaderBuffer[40] = inputData;
	int DataBufferA(inputData + 36);
	ExportWavHeaderBuffer[7] = DataBufferA >> 24;
	ExportWavHeaderBuffer[6] = DataBufferA >> 16;
	ExportWavHeaderBuffer[5] = DataBufferA >> 8;
	ExportWavHeaderBuffer[4] = DataBufferA;

}
WavRW::~WavRW()
{
	//free(ImportWavFileName);
	free(ImporAudioDataBufferShort);
}

//Import Wav
void ImportWavFile(const char WavFileName[10])
{
	//Set File Point
	WavRW wavFile1;
	//Set wav File Name
	wavFile1.ImportWavFileName = WavFileName;

	//Read wav File
	wavFile1.ImportWav();

	//ShowImportAudioInfo
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

	//Create wav File
	ExportWavFile1.CreateExportWavFile();

	//Set sampling Rate
	ExportWavFile1.SetSampleingRate(16000);

	//Set Export Data
	int ExportAudioDataSizeShort(30000); //ExportAudioDataSizeShort
	ExportWavFile1.ExportAudioDataSizeChar = ExportAudioDataSizeShort * 2;
	ExportWavFile1.ExportAudioDataBufferChar = new char[ExportWavFile1.ExportAudioDataSizeChar];
	int DataBufferA(0);
	float inputFre(440);
	//BufferFre
	float BufferFre(0);
	BufferFre = ExportWavFile1.ExportSamplingRate / 360*57.3;
	//
	for (int i(0); i < ExportAudioDataSizeShort; i++)
	{
		//printf("%f\n",cos(440*i / 57.3/44.4));
		//if (i > 361) break;
		DataBufferA = 5000 * cos(inputFre * (float)i / BufferFre);  //44.4=16000/360=sampling rate/360
		ExportWavFile1.ExportAudioDataBufferChar[2 * i] = DataBufferA;
		ExportWavFile1.ExportAudioDataBufferChar[2 * i + 1] = DataBufferA >> 8;
	}

	//test
	//exit(0);

	
	//Set Data Size
	ExportWavFile1.SetExportAudioSize(ExportWavFile1.ExportAudioDataSizeChar);

	//Export Header
	ExportWavFile1.ExportWavHeader();

	//Export Audio Data
	ExportWavFile1.ExportAudioData();

}
int main()
{

	// Export wav file
	const char* ExportWavFileName = "ExportWav.wav";
	ExportWavFile(ExportWavFileName);

	// Import wav file
	const char* ImportWavFileName = "ExportWav.wav";
	//ImportWavFile(ImportWavFileName); 

	system("pause");
	return 0;
}


