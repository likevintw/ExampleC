

//sound detection R5 20190614_1409

#include <fstream>
#include <time.h> //for time()
#include <vector> //for vector
#include <fstream>
using namespace std;

#include "T3T4_alert_R2.h"

//Reading all of files in a folder
/*
input the folder name
output vecImages[iaudioidx].c_str()
output vecImages.size()
*/
std::vector<std::string> StrSplit(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str = str + pattern;

	for (int i = 0; i < str.size(); i++)
	{
		pos = str.find(pattern, i);
		if (pos < str.size())
		{
			std::string s = str.substr(i, pos - 1);
			if (s.length() > 1)
			{
				s = s.substr(0, s.length() - 1);
			}

			if (i > 0)
			{
				result.push_back(s);
			}
			i = pos + pattern.size() - 1;
		}
	}

	return result;
}
std::string GetExtensionName(const std::string & strFile)
{
	std::vector<std::string> strs = StrSplit(strFile, ".");
	return strs[strs.size() - 1];
}
#ifdef _MSC_VER
#include <windows.h>
#endif
std::vector<std::string> GetFileNameListInDir(std::string targetDir)
{
	std::vector<std::string> nameList;

#ifdef _MSC_VER
	//windows x64
	std::string search_path = targetDir + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) //is fd not a folder? (is file)
			{
				std::string strFind = fd.cFileName;// FindFileData.cFileName;
				std::string exten_name = GetExtensionName(strFind);

				if (("raw" == exten_name || "RAW" == exten_name || "wav" == exten_name || "WAV" == exten_name))
				{
					std::string stImage = targetDir + "/" + strFind;
					//std::cout << vecImages.size() << std::endl;
					nameList.push_back(stImage);
					//nameList.push_back(fd.cFileName);
				}
				//nameList.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
#else
	//linux
	std::string search_path = targetDir;
	DIR* dir = opendir(search_path.c_str());
	struct dirent* ent;
	while ((ent = readdir(dir)) != NULL)
	{
		std::string name = ent->d_name;
		if (name[0] != '.')
		{
			//check it is file
			std::string myPath = targetDir + "/" + name;
			struct stat mybuf;
			stat(myPath.c_str(), &mybuf);
			bool isFileFlag = S_ISREG(mybuf.st_mode);
			if (isFileFlag == true)
			{
				nameList.push_back(myPath);
			}
		}
	}
	closedir(dir);
#endif
	return nameList;
}

class txt_file_class
{
public:

	const char* txt_file_name;
	int* short_reading_data;
	long reading_data_size;
	double writing_data;
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
		txt_file << writing_data;
		txt_file << '\n';
		txt_file.close();
	}
	~txt_file_class()
	{
		delete short_reading_data;
		short_reading_data = NULL;
	}
};

class RW_wav
{
public:
	const char* wav_name;
	FILE* pFile; //file point
	long wav_data_size;  //The size of file stream
	long short_data_size; //The size of buffer with short type (Important)
	short* wav_data_buffer; //data buffer, the wav data is 16bits, so using short type
	size_t result;
	RW_wav()
	{
		wav_name = "Please define the wav_name";
	}
	void read_wav()
	{
		pFile = fopen(wav_name, "rb");
		if (pFile == NULL) {
			fputs("File opening fail, please check the file or the definition of wav_name", stderr);
			exit(1);
		}
		//
		fseek(pFile, 0, SEEK_END); //Set the location to the end of file
		wav_data_size = ftell(pFile); //Returns the end-location value of the position indicator of the stream.
		short_data_size = wav_data_size / 2;
		//printf("The size of file=%d\n", wav_data_size);
		rewind(pFile);

		// allocate memory to contain the whole file:
		wav_data_buffer = (short*)malloc(sizeof(short) * wav_data_size); //set a space for buffer, buffer_size=data_type*data number
		if (wav_data_buffer == NULL) { fputs("Memory error", stderr); exit(2); } //Check

		// copy the file into the buffer:
		result = fread(wav_data_buffer, 1, wav_data_size, pFile);
		if (result != wav_data_size) { fputs("Reading error", stderr); exit(3); } //Check


		//Release the file point
		fclose(pFile);
	}
	~RW_wav()
	{
		//
		//delete wav_name;
		//delete wav_data_buffer;
		//
		//wav_name = NULL;
		//wav_data_buffer = NULL;
	}
};

void DoOnlyOnece()
{
	//T3T4_alert_R2 definition
	glass_broken_alert_R1 wav_fft;

	//Please check all of the items below each project
	wav_fft.input_data_size = 500;
	wav_fft.sampling_rate = 44100;
	wav_fft.buffer_frequency_variance_threshold = 20;
	wav_fft.buffer_amplitude_threshold = 0; //
	wav_fft.max_buffer_amplitude_value = 0; // the maximum value in the buffer
	wav_fft.buffer_amplitude_threshold_rate = 0.1;

	//
	wav_fft.alert_initial(); //T3T4_alert_R2 alert_initial
	wav_fft.fft_array_initial();
	wav_fft.fft_x_axis(); // needs input_data_size

	printf("initial done\n");

	//Read a wav file
	RW_wav wav_file_1;
	wav_file_1.wav_name = "bosch1_16k.wav";
	wav_file_1.read_wav();


	while (1)
	{

		//Get data of the fft_buffer
		/**/
		for (int i(0); i < wav_fft.input_data_size; i++)
		{
			wav_fft.input_t_data[i] = wav_file_1.wav_data_buffer[i];
		}


		//Do FFT Algorithm
		wav_fft.FFT_2_radix(); //Do FFT()			


		//reset the alert counters
		wav_fft.audio_alert_flag = 0;

		//Do the alert detection
		wav_fft.glass_broken_detection();


		//if the alert is found
		if (wav_fft.audio_alert_flag == 1)
		{
			printf("The alert is found\n");
		}

		//break for while loop
		break;
	}
	system("pause");
}

class convolution_integral
{
public:
	int data_size;
	short* input_data_1, * input_data_2;
	int value_buffer;
	int* output_data;
	convolution_integral()
	{
		data_size = 10;
		input_data_1 = new short[data_size];
		input_data_2 = new short[data_size];
		output_data = new int[data_size];
	}
	void convolution_integral_initial()
	{
		delete input_data_1, input_data_2, output_data;
		input_data_1 = NULL;
		input_data_2 = NULL;
		output_data = NULL;
		input_data_1 = new short[data_size];
		input_data_2 = new short[data_size];
		output_data = new int[data_size];

		//initial
		/*
		for (int i(0); i < data_size ; i++)
		{
			input_data_1[i] = 0;
		}
		*/
	}
	void convolution_integral_algorithm()
	{
		//from 0 to N-1
		for (int i(0); i < data_size; i++)
		{
			value_buffer = 0;
			for (int j(0); j < data_size; j++)
			{
				if ((i-j)<0)
				{
					value_buffer = value_buffer + input_data_1[data_size+i-j] * input_data_2[j];
					//printf("%d %d %d %d\n", i, j, input_data_1[j], input_data_2[j]);
				}
				else
				{
					value_buffer = value_buffer + input_data_1[i - j] * input_data_2[j];
					//printf("%d %d %d %d\n", i, j, input_data_1[j], input_data_2[j]);
				}
				//printf("%d %d %d\n", i, j,value_buffer);
			}
			output_data[i] = value_buffer;
			//printf("%d \n", output_data[i]);
		}
	}
	~convolution_integral()
	{
		//delete input_data_1,input_data_2,output_data; 
		input_data_1 = NULL;
		input_data_2 = NULL;
		output_data = NULL;
	}
};

int main()
{
	
	//txt class definition
	txt_file_class text1,text2;
	text1.txt_file_name = "input_normalized1.txt";
	text2.txt_file_name = "input_normalized2.txt";
	text1.create_textfile();
	text2.create_textfile();

	//Read a wav file
	RW_wav wav1, wav2;
	wav1.wav_name = "2.wav";
	wav2.wav_name = "2.wav";
	
	wav1.read_wav();
	wav2.read_wav();
	//printf("%d %d \n", wav1.wav_data_size, wav2.wav_data_size);

	

	//Control Parameters
	int file_header = 50;
	int data_size = 1024; //must larger than 250
	//double spetrum_sum(0);
	int data_sampling_rate = 44100;
	//int delta_i(0);

	glass_broken_alert_R1 fft1, fft2;
	fft1.input_data_size = data_size;
	fft2.input_data_size = data_size;
	fft1.fft_array_initial();
	fft2.fft_array_initial();
	if (wav2.short_data_size<wav1.short_data_size)
	{
		wav1.short_data_size = wav2.short_data_size;
	}
	
	
	//Get g(t) and h(t)
	//read the input buffer
	int array_buufer(0);
	array_buufer = (wav1.short_data_size-50) / data_size;
	/**/
	for (int i(file_header), j(0); j < data_size; i=i+ array_buufer, j++)
	{
		fft1.input_t_data[j] = wav1.wav_data_buffer[i]; // g(t)
		fft2.input_t_data[j] = wav2.wav_data_buffer[i]; // h(t)
		//printf("%d\n", fft1.input_t_data[j]);
		//printf("%d\n", fft2.input_t_data[j]);
		//printf("%d %d\n", i, j);
		//printf("%d \n", j);
	}
	

	//Convolution integral g * h
	convolution_integral convolution1;
	convolution1.data_size = data_size;
	convolution1.convolution_integral_initial();
	convolution1.input_data_1 = fft1.input_t_data;
	convolution1.input_data_2 = fft2.input_t_data;
	convolution1.convolution_integral_algorithm();
	// show the convolution result
	/**/
	//for (int i(0); i < (data_size/2); i++)
	for (int i(0); i < data_size; i++)
	{
		//printf("%d %d \n", i, convolution1.output_data[i]);
		printf("%d \n",  convolution1.output_data[i]);
	}
	

	//FFT G and H
	//fft1.FFT_2_radix(); //Get G
	//fft2.FFT_2_radix(); //Get H

	/*
	for (int i(0); i < (data_size/2); i++)
	{
		//printf("%f\n", fft1.output_data_Amplitude[i]); //show G
		//printf("%f\n", fft2.output_data_Amplitude[i]); //show H
		//printf("%f\n", fft1.output_data_Amplitude[i]*fft2.output_data_Amplitude[i]); //show GxH
		
		//text1.writing_data = fft1.output_data_Amplitude[i];
		//text2.writing_data = fft2.output_data_Amplitude[i];
		//text1.write_number_data_into_txt();
		//text2.write_number_data_into_txt();
	}
	*/
 	system("Pause");
	return 0;
}