

//glass broken detection R10 20190527_1321

#include <fstream>
#include <time.h> //for time()
#include <vector> //for vector

#include "glass_alert_R1.h"

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
	glass_broken_alert_R1 glass_detect_1;
	//Please check all of the items below each project
	glass_detect_1.input_data_size = 500; // The number of detecting points
	glass_detect_1.sampling_rate = 44100; //Hz pre second
	glass_detect_1.buffer_frequency_variance_threshold = 20; // The magnitude of frequency distribution
	glass_detect_1.buffer_amplitude_threshold = 0; //
	glass_detect_1.max_buffer_amplitude_value = 0; // the maximum value in the buffer
	glass_detect_1.buffer_amplitude_threshold_rate = 0.1; // The thershold of amplitude of spetrum
	glass_detect_1.frequency_detection_limited_min = 4410; //Unit: Hz
	glass_detect_1.frequency_detection_limited_max = 17640; //Unit: Hz
	// if the minimum setting is less than the half of sampling_rate 
	if (glass_detect_1.frequency_detection_limited_max > int(glass_detect_1.sampling_rate / 2))
	{
		glass_detect_1.frequency_detection_limited_max = glass_detect_1.sampling_rate / 2;
	}
	glass_detect_1.frequency_detection_limited_max_point = glass_detect_1.frequency_detection_limited_max * glass_detect_1.input_data_size / glass_detect_1.sampling_rate;
	glass_detect_1.frequency_detection_limited_min_point = glass_detect_1.frequency_detection_limited_min * glass_detect_1.input_data_size / glass_detect_1.sampling_rate;
	

	//
	glass_detect_1.alert_initial(); //T3T4_alert_R2 alert_initial
	glass_detect_1.fft_array_initial();
	glass_detect_1.fft_x_axis(); // needs input_data_size

	printf("initial done\n");

	//Read a wav file
	RW_wav wav_file_1;
	wav_file_1.wav_name = "bosch1_16k.wav";
	wav_file_1.read_wav();


	while (1)
	{

		//Get data of the fft_buffer
		/**/
		for (int i(0); i < glass_detect_1.input_data_size; i++)
		{
			glass_detect_1.input_t_data[i] = wav_file_1.wav_data_buffer[i];
		}


		//Do FFT Algorithm
		glass_detect_1.FFT_2_radix(); //Do FFT()			


		//reset the alert counters
		glass_detect_1.audio_alert_flag = 0;

		//Do the alert detection
		glass_detect_1.glass_broken_detection();


		//if the alert is found
		if (glass_detect_1.audio_alert_flag == 1)
		{
			printf("The alert is found\n");
		}

		//break for while loop
		break;
	}
	system("pause");
}


//test
short fail_counter(0);
void ReadOneFile(std::string strFileName)
{
	glass_broken_alert_R1 glass_detect_1;
	//Please check all of the items below each project
	glass_detect_1.input_data_size = 500; // The number of detecting points
	glass_detect_1.sampling_rate = 44100; //Hz pre second
	glass_detect_1.buffer_frequency_variance_threshold = 20; // The magnitude of frequency distribution
	glass_detect_1.buffer_amplitude_threshold = 0; //
	glass_detect_1.max_buffer_amplitude_value = 0; // the maximum value in the buffer
	glass_detect_1.buffer_amplitude_threshold_rate = 0.1; // The thershold of amplitude of spetrum
	glass_detect_1.frequency_detection_limited_min = 4410; //Unit: Hz
	glass_detect_1.frequency_detection_limited_max = 17640; //Unit: Hz
	// if the minimum setting is less than the half of sampling_rate 
	if (glass_detect_1.frequency_detection_limited_max > int(glass_detect_1.sampling_rate / 2))
	{
		glass_detect_1.frequency_detection_limited_max = glass_detect_1.sampling_rate / 2;
	}
	glass_detect_1.frequency_detection_limited_max_point= glass_detect_1.frequency_detection_limited_max * glass_detect_1.input_data_size/ glass_detect_1.sampling_rate;
	glass_detect_1.frequency_detection_limited_min_point = glass_detect_1.frequency_detection_limited_min * glass_detect_1.input_data_size/ glass_detect_1.sampling_rate;
	//

	//
	glass_detect_1.alert_initial(); //glass_detect_1 alert_initial
	glass_detect_1.fft_array_initial();
	glass_detect_1.fft_x_axis(); // needs input_data_size

	//printf("initial done\n");

	//Read a wav file
	RW_wav wav_file_1;
	wav_file_1.wav_name = strFileName.c_str();
	wav_file_1.read_wav();

	//printf("wav_data_size = %d\n", wav_file_1.wav_data_size);



	int iWavSegmentation = wav_file_1.wav_data_size / glass_detect_1.input_data_size;

	//To get the buffer max. amplitude value
	/**/
	for (int iseg = 1; iseg < iWavSegmentation; iseg++)
	{

		//Get data of the fft_buffer
		for (int i(0); i < glass_detect_1.input_data_size; i++)
		{
			glass_detect_1.input_t_data[i] = wav_file_1.wav_data_buffer[iseg * glass_detect_1.input_data_size + i];
		}

		//Do FFT Algorithm
		glass_detect_1.FFT_2_radix(); //Do FFT()			


		//To get the buffer max. amplitude value
		for (int i(1); i < glass_detect_1.input_data_size/2-50; i++)//Find the buffer max. value in the spectrum of .wav
		{
			if (glass_detect_1.output_data_Amplitude[i]> glass_detect_1.max_buffer_amplitude_value)
			{
				glass_detect_1.max_buffer_amplitude_value = glass_detect_1.output_data_Amplitude[i];
			}
		}
	}
	

	//printf("%f\n", glass_detect_1.max_buffer_amplitude_value);
	//glass broken detection
	for (int iseg = 0; iseg < iWavSegmentation; iseg++)
	{

		//Get data of the fft_buffer
		/**/
		for (int i(0); i < glass_detect_1.input_data_size; i++)
		{
			glass_detect_1.input_t_data[i] = wav_file_1.wav_data_buffer[iseg * glass_detect_1.input_data_size + i];
		}

		//Do FFT Algorithm
		glass_detect_1.FFT_2_radix(); //Do FFT()		

		//
		glass_detect_1.audio_alert_flag = 0;

		//glass_broken_detection
		glass_detect_1.glass_broken_detection();

		if (glass_detect_1.audio_alert_flag != 0)
		{
			//printf("glass broken detected\n");
			break;
		}
		//printf("Do FFT %d/%d\n", iseg, iWavSegmentation);

		//break for while loop
		//break;
	}
	if (glass_detect_1.audio_alert_flag == 0)
	{
		fail_counter++;
		//printf("%d\n", fail_counter);
		//printf("%s\n", strFileName.c_str());
	}
}

void main()
{
	std::vector<std::string> dataname = GetFileNameListInDir("test");
	for (int i = 0; i < dataname.size(); i++)
	{
		printf("\n%d/%d %s\n", i + 1, dataname.size(), dataname[i].c_str()); 
		ReadOneFile(dataname[i]);
		printf("%d\n", fail_counter);
	}

	system("pause");
}