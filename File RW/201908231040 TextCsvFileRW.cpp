/*
TextCsvFileRW 201908231040

*/

#include <iostream>
#include <fstream>

using namespace std;

//
class TextFileRW
{
public:
	//Attribute
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
	void CreateExportFile();
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
void TextFileRW::CreateExportFile() //create a file
{
	std::ofstream txt_file;
	txt_file.open(ExportTextFileName, ios::out | ios::trunc);
	//Check the text file, if it is created fail, show the warming information
	if (!txt_file)
	{
		cout << endl;
		cout << "Export_file is opened fail" << endl;
		cout << endl;
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

//Read Data Sizw
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
	}

	//Reading data from text
	for (unsigned int i(0);; i++)
	{
		txt_file >> ReadIntBuffer[i];
		cout << "Date " << i << " is: " << ReadIntBuffer[i] << endl;
	}

}
/**/


int main()
{
	cout << "Read/Write Text File" << endl;
	/**/
	TextFileRW ExportCsvFile;
	//Export Data into csv
	ExportCsvFile.ExportTextFileName = "TextExportTest.csv";
	ExportCsvFile.CreateExportFile(); //create an export file
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

	//Export Data into text
	TextFileRW ExportTextFile1;
	ExportTextFile1.ExportTextFileName = "ExportTextFile.txt";
	ExportTextFile1.CreateExportFile(); //create an export file
	ExportCsvFile.OutputBufferInt = 1;
	ExportCsvFile.ExportDataInt();
	ExportCsvFile.ExportChangeLine();
	ExportCsvFile.OutputBufferInt = 2;
	ExportCsvFile.ExportDataInt();

	//
	cout << "End" << endl;
	return 0;
}