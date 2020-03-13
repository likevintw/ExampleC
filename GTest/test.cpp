#include "pch.h"
#include <windows.h> //for Sleep(100);
#include <ctime>
#include <thread>
#include<stdio.h>
#include <fstream>
using namespace std;
short state_code(0);
/**/
void create_textfile(const char* txtFileName)
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
void WriteData(const char* txtFileName, std::string OutputCharDate)
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
int Testing(int index)
{
	if (index == 1)
	{
		printf("Start of export to a file\n");
		// create a file
		// exprot logs
		create_textfile("ExportLog.txt");
		//std::string buffer(0);
		for (int i(0); i < 10; i++)
		{
			//printf("Log to File %d\n", i + 1);
			Sleep(1500);
			WriteData("ExportLog.txt", "Log to File");
		}
		// close file
		printf("End of export to a file\n");
		return 1;
	}
	if (index == 2)
	{
		printf("Start of export to the terminal\n");
		for (int i(0); i < 10; i++)
		{
			printf("Log to Terminal %d\n", i + 1);
			Sleep(1500);
		}
		printf("End of export to the terminal\n");
		return 1;
	}
}


TEST(Testing, TestTesting) {
    EXPECT_EQ(1, Testing(1));
	EXPECT_EQ(1, Testing(2));
    EXPECT_TRUE(true);
}

