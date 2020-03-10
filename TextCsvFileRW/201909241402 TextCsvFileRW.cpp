/*
TextCsvFileRW 201909241402
Write value into Text file >> OK
Write value into Csv file >> OK
Read character from text >> OK
Read character from CSV >> OK
Read int from CSV  
Read double from CSV 
Read vale from Text file
*/

//Reference
/*
#include <fstream>
#include <string>
#include <string.h>

int main()
{
	std::ifstream is("info.csv");

	std::string line;
	while (std::getline(is, line))
	{
		const char *begin = line.c_str();

		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			std::string column1(begin, end - begin);
			std::cout << column1 << std::endl;
		}
	}
	return 0;
}
*/

#include <iostream>
#include <fstream>

using namespace std;

//
class TextFileRW
{
public:
	//Name
	const char* ExportFileName;
	const char* ImportFileName;
	//Export
	char OutputBufferChar;
	int OutputBufferInt;
	//Import
	int* ReadIntBuffer;
	int ReadDateSize;
	//Method
	TextFileRW();
	//Export
	void CreateExportTextFile();
	void ExportChangeLine();
	void ExportDot();
	void ExportDataChar();
	void ExportDataInt();
	//Import
	void CheckImportTextFile();
	void ImportDataChar();
	void ImportDataInt();
};

//Method
//constructor
TextFileRW::TextFileRW()
{

}
//Create Export Text File
//create txt file
void TextFileRW::CreateExportTextFile() //create a file
{
	std::ofstream txt_file;
	txt_file.open(ExportFileName, ios::out | ios::trunc);
	//Check the text file, if it is created fail, show the warming information
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n")
	}
	txt_file.close();
}//create a txt file
//Export Data
void TextFileRW::ExportDataChar() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportFileName, ios::out | ios::app);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n")
	}
	txt_file << OutputBufferChar;
	txt_file.close();
}
void TextFileRW::ExportDataInt() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportFileName, ios::out | ios::app);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n")
	}
	txt_file << OutputBufferInt;
	txt_file.close();
}
void TextFileRW::ExportDot() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportFileName, ios::out | ios::app);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n")
	}


	char changeLine[1];
	changeLine[0] = ',';
	txt_file << changeLine[0];

}
void TextFileRW::ExportChangeLine() //write_number_data_into_txt
{
	std::ofstream txt_file;
	txt_file.open(ExportFileName, ios::out | ios::app);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n");
	}

	//case 1: C
	/*
	char changeLine[1];
	changeLine[0] = '\n';
	txt_file << changeLine[0];*/

	//case 2: C++
	txt_file << endl;
	txt_file.close();
}

//Read Data number
//initial data buffer
//Read int Data
void TextFileRW::CheckImportTextFile() //read_number_and_dataNumber_from_txt
{

	//Check the text file, if it is not exit, show the warming information
	ifstream txt_file(ExportFileName, ios::in);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		//printf("\nExport_file is opened fail\n")
	}

	//Reading data from text
	for (unsigned int i(0);; i++)
	{
		txt_file >> ReadIntBuffer[i];
		cout << "Date " << i << " is: " << ReadIntBuffer[i] << endl;
	}

}
//
void TextFileRW::ImportDataChar()
{
	//Check the text file, if it is not exit, show the warming information
	ifstream txt_file(ImportFileName, ios::in);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}

	//Reading data from text
	/**/
	char c;
	int BufferInt(0);
	while (txt_file.good()) 
	{
		//std::cout << c;
		c = txt_file.get();
		BufferInt = int(c);
		//Present Data
		//Change Line in int type is 10
		//printf("%c", c);
		//printf("%d\n",  BufferInt-48);
		printf("%c", BufferInt);
	}

	txt_file.close();
}
//
void TextFileRW::ImportDataInt()
{
	int test(0);
	int reading_data_size(0);
	float* short_reading_data;
	//Check the text file, if it is not exit, show the warming information
	ifstream txt_file(ImportFileName, ios::in);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	
	//
	txt_file.seekg(0, txt_file.end);
	reading_data_size = txt_file.tellg();
	reading_data_size = reading_data_size/2;
	txt_file.seekg(0, txt_file.beg);
	printf("Size of file is %d\n", reading_data_size);
	short_reading_data = new float[reading_data_size];
	//Reading data from text
	/**/
	for (unsigned int i(0);; i++)
	{
		if (!txt_file.good())
		{
			//break;
		}
 		txt_file >> short_reading_data[i];
		printf("%f\n", short_reading_data[i]);
		
	}

	txt_file.close();
}
/**/


int main()
{
	cout << "Read/Write Text File" << endl;
	/*
	TextFileRW ExportCsvFile;
	//Export Data into csv
	ExportCsvFile.ExportTextFileName = "TextExportTest.csv";
	ExportCsvFile.CreateExportTextFile(); //create an export file
	ExportCsvFile.OutputBufferChar = 'A';
	ExportCsvFile.ExportDataChar();
	ExportCsvFile.ExportDot();
	ExportCsvFile.OutputBufferChar = 'B';
	ExportCsvFile.ExportDataChar();
	ExportCsvFile.ExportChangeLine();
	ExportCsvFile.OutputBufferInt = 1;
	ExportCsvFile.ExportDataInt();
	ExportCsvFile.ExportDot();
	ExportCsvFile.OutputBufferInt = 2;
	ExportCsvFile.ExportDataInt();*/

	//Export Data into text
	/*
	TextFileRW ExportTextFile1;
	ExportTextFile1.ExportTextFileName = "ExportTextFile.txt";
	ExportTextFile1.CreateExportTextFile(); //create an export file
	ExportCsvFile.OutputBufferInt = 1;
	ExportCsvFile.ExportDataInt();
	ExportCsvFile.ExportChangeLine();
	ExportCsvFile.OutputBufferInt = 2;
	ExportCsvFile.ExportDataInt();*/

	//
	TextFileRW ImportDataA;
	ImportDataA.ImportFileName = "ExportData.csv";
	ImportDataA.ImportDataChar();
	//ImportDataA.ImportDataInt();
	//
	cout << "End" << endl;
	return 0;
}