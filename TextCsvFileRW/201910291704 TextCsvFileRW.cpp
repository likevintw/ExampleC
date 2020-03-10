/*
201910291704 TextCsvFileRW 
ExportAppendCsvFile() >>OK
ExporAppendTextFile() >>OK
Read vale from Text file
*/
#include <iostream>
#include <fstream>

using namespace std;

//
class TextFileRW
{
public:
	//Name
	const char* ExportTextFileName;
	const char* ImportTextFileName;
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
	void CreateImportTextFile();
	void ReadTxtIntData();
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
	txt_file.open(ExportTextFileName, ios::out | ios::trunc);
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
	txt_file.open(ExportTextFileName, ios::out | ios::app);
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
	txt_file.open(ExportTextFileName, ios::out | ios::app);
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
	txt_file.open(ExportTextFileName, ios::out | ios::app);
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
	txt_file.open(ExportTextFileName, ios::out | ios::app);
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
		printf("\nExport_file is opened fail\n");
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
void TextFileRW::ReadTxtIntData() //read_number_and_dataNumber_from_txt
{

	//Check the text file, if it is not exit, show the warming information
	ifstream txt_file(ImportTextFileName, ios::in);
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
/**/

//ExportCsvFile
void ExportAppendCsvFile()
{
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
	ExportCsvFile.ExportDataInt();
}
//ExportTextFile
void ExporAppendTextFile()
{
	//Export Data into text
	TextFileRW ExportTextFile1;
	ExportTextFile1.ExportTextFileName = "ExportTextFile.txt";
	ExportTextFile1.CreateExportTextFile(); //create an export file
	ExportTextFile1.OutputBufferInt = 1;
	ExportTextFile1.ExportDataInt();
	ExportTextFile1.ExportChangeLine();
	ExportTextFile1.OutputBufferInt = 2;
	ExportTextFile1.ExportDataInt();
}

int main()
{
	cout << "Read/Write Text File" << endl;
	/**/
	
	//ExportAppendCsvFile
	ExportAppendCsvFile();
	//ExporAppendTextFile
	ExporAppendTextFile();

	cout << "End" << endl;
	return 0;
}