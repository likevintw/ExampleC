/*
Text File R6 201908111358

1.Create a text file
2.read the number and the number of data from text file
3.write a number datum into text file

*/

#include <fstream>

using namespace std;
class txt_file_class
{
public:

	
	//Attribute
	const char* txtFileName;
	long ReadDataSize;
	//Read
	int* ReadShortData;
	//Write
	short OutputShortData;
	char OutputCharDate;
	char OutputBin4Bits[4];

	//Method
	txt_file_class();
	void create_textfile(); //creat txt file
	void read_data_short(); //read_number_and_dataNumber_from_txt
	//Write
	void WriteShortData(); //write_number_data_into_txt
	void WriteCharData();
	void WriteBin4Bits();
	~txt_file_class();
	
};
txt_file_class::txt_file_class()
{
	
}
void txt_file_class::create_textfile() //create a txt file
{
	std::ofstream txt_file;
	txt_file.open(txtFileName, ios::out | ios::trunc);
	//Check the text file, if it is created fail, show the warming information
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	txt_file.close();
}
//read_number_and_dataNumber_from_txt
void txt_file_class::read_data_short()
{
	
}
void txt_file_class::WriteShortData()
{
	std::ofstream txt_file;
	txt_file.open(txtFileName, ios::out | ios::app);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	txt_file << OutputShortData;
	txt_file << '\n';
	txt_file.close();
}
void txt_file_class::WriteCharData()
{
	std::ofstream txt_file;
	txt_file.open(txtFileName, ios::out | ios::app);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	txt_file << OutputCharDate;
	txt_file << '\n';
	txt_file.close();
}
//
/**/
void txt_file_class::WriteBin4Bits()
{
	std::ofstream txt_file;
	txt_file.open(txtFileName, ios::out | ios::app);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	for (short i(0); i < 4; i++)
	{
		txt_file << OutputBin4Bits[i];
	}
	txt_file << '\n';
	txt_file.close();
}
//
txt_file_class::~txt_file_class()
{
	delete ReadShortData;
	ReadShortData = NULL;
}


char* itobs(short n ) 
{
	char *ps=new char [8 * sizeof(short) + 1];
	int size = 8 * sizeof(char);
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
	printf("Read/Write Text File\n");
	txt_file_class file1;
	file1.txtFileName = "data22.txt";
	file1.create_textfile();
	for (int i(-5); i < 5; i++)
	{
		//Write Short
		/*
		file1.OutputShortData = i;
		file1.WriteShortData();*/

		//Write Char
		/*
		file1.OutputCharDate = i+65;
		file1.WriteCharData();*/

		//Write Bin 4 Bits
		/*
		file1.OutputCharDate = i+65;
		file1.WriteCharData();*/
		//printf("%d = %s\n", i, itobs(i));
	}
	//file1.read_data_short();

	printf("End");
	return 0;
}
