

//glass broken detection R8 20190523_1523

#include <fstream>
#include <time.h> //for time()
#include <vector> //for vector

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
	}
	void read_wav()
	{
		pFile = fopen(wav_name, "rb");
		if (pFile == NULL) {
			fputs("File error", stderr);
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
	//Please check all of the items below
	wav_fft.sampling_rate = 16000; //unit: Hz
	wav_fft.input_data_size = 500; //The number of sampling points

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


void ReadOneFile(std::string strFileName)
{
	glass_broken_alert_R1 wav_fft;
	//Please check all of the items below
	wav_fft.sampling_rate = 44100; //unit: Hz
	wav_fft.input_data_size = 500; //The number of sampling points
	wav_fft.buffer_frequency_variance_threshold = 20;
	wav_fft.buffer_amplitude_threshold_rate = 0.1;

	//
	wav_fft.alert_initial(); //T3T4_alert_R2 alert_initial
	wav_fft.fft_array_initial();
	wav_fft.fft_x_axis(); // needs input_data_size

	printf("initial done\n");

	//Read a wav file
	RW_wav wav_file_1;
	wav_file_1.wav_name = strFileName.c_str();
	wav_file_1.read_wav();

	//printf("wav_data_size = %d\n", wav_file_1.wav_data_size);



	int iWavSegmentation = wav_file_1.wav_data_size / wav_fft.input_data_size;

	//To get the buffer max. amplitude value
	for (int iseg = 0; iseg < iWavSegmentation; iseg++)
	{

		//Get data of the fft_buffer
		/**/
		for (int i(0); i < wav_fft.input_data_size; i++)
		{
			wav_fft.input_t_data[i] = wav_file_1.wav_data_buffer[iseg * wav_fft.input_data_size + i];
		}

		//Do FFT Algorithm
		wav_fft.FFT_2_radix(); //Do FFT()			


		//To get the buffer max. amplitude value
		/**/
		for (int i(1); i < wav_fft.input_data_size/2-50; i++)
		{
			if (wav_fft.output_data_Amplitude[i]> wav_fft.max_buffer_amplitude_value)
			{
				wav_fft.max_buffer_amplitude_value = wav_fft.output_data_Amplitude[i];
			}
		}
	}

	//printf("%f\n", wav_fft.max_buffer_amplitude_value);
	//glass broken detection
	for (int iseg = 0; iseg < iWavSegmentation; iseg++)
	{

		//Get data of the fft_buffer
		/**/
		for (int i(0); i < wav_fft.input_data_size; i++)
		{
			wav_fft.input_t_data[i] = wav_file_1.wav_data_buffer[iseg * wav_fft.input_data_size + i];
		}

		//Do FFT Algorithm
		wav_fft.FFT_2_radix(); //Do FFT()		

		//
		wav_fft.audio_alert_flag = 0;

		//glass_broken_detection
		wav_fft.glass_broken_detection();

		if (wav_fft.audio_alert_flag != 0)
		{
			printf("glass broken detected\n");
		}
		//printf("Do FFT %d/%d\n", iseg, iWavSegmentation);



		//break for while loop
		//break;
	}
}

void main()
{
	std::vector<std::string> dataname = GetFileNameListInDir("test");
	for (int i = 0; i < dataname.size(); i++)
	{
		printf("\n%d/%d %s\n", i, dataname.size(), dataname[i].c_str());
		ReadOneFile(dataname[i]);
	}

	system("pause");
}