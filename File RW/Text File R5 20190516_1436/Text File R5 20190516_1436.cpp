/*
Text File R5 20190516_1436

1.Create a text file
2.read the number and the number of data from text file
3.write a number datum into text file

*/

#include <fstream>

using namespace std;
class txt_file_class
{
public:

	const char* txt_file_name;
	int* short_reading_data;
	long reading_data_size;
	short int_writing_data;
	txt_file_class()
	{
		reading_data_size = 10;
		short_reading_data = new int[reading_data_size];
	}
	void create_textfile() //create a file
	{
		std::ofstream txt_file;
		txt_file.open(txt_file_name, ios::out | ios::trunc);
		//Check the text file, if it is created fail, show the warming information
		if (!txt_file)
		{
			printf("Export_file is opened fail\n");
		}
		txt_file.close();
	}//create a txt file
	void read_data_short() //read_number_and_dataNumber_from_txt
	{
		int test(0);
		//Check the text file, if it is not exit, show the warming information
		ifstream txt_file(txt_file_name, ios::in);
		if (!txt_file)
		{
			printf("Export_file is opened fail\n");
		}

		txt_file.seekg(0, txt_file.end); 
		reading_data_size = txt_file.tellg();
		//printf("Size of file is %d\n", reading_data_size);
		txt_file.seekg(0, txt_file.beg);
		short_reading_data = new int[reading_data_size];
		//Reading data from text
		/**/
		for (unsigned int i(0);; i++)
		{
			if (txt_file.eof()) //
			{
				reading_data_size = i;
				break;
			}
			txt_file >> short_reading_data[i];
			//printf("%d\n", short_reading_data[i]);
		}
		
		txt_file.close();
	}
	void write_number_data_into_txt() //write_number_data_into_txt
	{
		std::ofstream txt_file;
		txt_file.open(txt_file_name, ios::out | ios::app);
		if (!txt_file)
		{
			printf("Export_file is opened fail\n");
		}
		txt_file << int_writing_data;
		txt_file << '\n';
		txt_file.close();
	}
	~txt_file_class()
	{
		delete short_reading_data;
		short_reading_data = NULL;
	}
};


int main()
{
	printf("Read/Write Text File\n");
	txt_file_class file1;
	file1.txt_file_name = "data22.txt";
	file1.create_textfile();
	for (int i(0); i < 14; i++)
	{
		file1.int_writing_data = i;
		file1.write_number_data_into_txt();
	}
	file1.read_data_short();
	/**/
	for (int i(0); i < file1.reading_data_size; i++)
	{
		printf("%d\n", file1.short_reading_data[i]);
	}
	
	printf("End");
	return 0;
}
