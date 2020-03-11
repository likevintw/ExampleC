
// File Import and Export A1

#include <iostream>
#include <fstream>


void ifstreamImport()
{
	char FileName[30] = "ImportTest.txt";
	std::ifstream myfile(FileName);
	char DataBuffer(0);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			myfile.get(DataBuffer);
			printf("%c\n", DataBuffer);
		}
		myfile.close();
	}
	else
	{
		printf("Open File %s Fail\n", FileName);
		exit(0);
	}
}
void ofstreamExport()
{
	char FileName[30] = "ExportTest.txt";
	std::ofstream fout;
	fout.open(FileName);
	if (!fout) 
	{
		printf("Open File %s Fail\n", FileName);
		exit(1);
	}
	printf("Keyin the text, enter 'q' to leave\n");
	char dataBuffer(0);
	/**/
	while (1)
	{
		if (scanf("%c", &dataBuffer))
		{
			if (dataBuffer == 'q')
			{
				break;
			}
			fout.put(dataBuffer);
		}
	}
	
	fout.close();
	
}
void fstreamImport()
{

	// Set AAC File Name
	char FileName[30] = "ImportTest.txt";
	// Open and Read AAC file
	std::fstream File;
	// Open AAC File
	File.open(FileName, std::ios::in);
	if (!File)
	{
		printf("Open AAC File %s Error\n", FileName);
		//fputs("File error", stderr);
		exit(1);
	}

	// Get AAC Data Number of File
	File.seekp(0, File.end);
	int DataSize(1000);
	DataSize = File.tellp();
	printf("AacDataSize:%d\n", DataSize);
	File.seekp(0, File.beg);

	// Read AAC Data
	File.seekp(0, File.beg);
	char* DataBuffer;
	DataBuffer = new char[DataSize];
	File.read(DataBuffer, DataSize);

	// Show the AAC File Data
	/*
	for (int i(0); i < 10; i++)
	{
		printf("%c\n", AacDataBuffer[i]);
	}
	*/
	// Close File
	File.close();
}

int main() 
{
	printf("fstream Import and Export Example\n");

	//ifstreamImport
	//ifstreamImport();

	//ifstreamExport

	//fstreamImport
	//fstreamImport();
	
	//ofstream Export, cover the exist data.
	ofstreamExport(); 

	//ofstream Export, keep the exist data, put the new data from the tail of file.

	//FILE* Import

	//FILE* Export

	return 0;
}