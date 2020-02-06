

//sound detection R6 20190617_1114

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

//
int pattern_spectrum_value[11][250] =
{
	//pattern 0
	{0}
	//pattern 1
	,{
12784	,
5958	,
8805	,
8809	,
5598	,
12161	,
3727	,
2582	,
14242	,
10614	,
3408	,
14580	,
4944	,
3897	,
10000	,
11671	,
9152	,
11377	,
7817	,
4994	,
8684	,
19314	,
6343	,
7171	,
4604	,
13139	,
7322	,
8314	,
11385	,
5611	,
11117	,
7567	,
6031	,
3106	,
11827	,
11890	,
8605	,
6008	,
13193	,
7629	,
2303	,
4674	,
1760	,
6506	,
4700	,
3114	,
4521	,
5784	,
9739	,
15285	,
3603	,
9359	,
4023	,
3332	,
10426	,
4214	,
7608	,
20779	,
4805	,
22509	,
31550	,
27317	,
92997	,
466541	,
304060	,
118683	,
99123	,
49605	,
48282	,
25408	,
11625	,
24838	,
25760	,
12046	,
10288	,
11866	,
23386	,
6325	,
2320	,
3097	,
14821	,
18334	,
11715	,
8658	,
13745	,
11301	,
10216	,
6957	,
18828	,
26990	,
36167	,
9426	,
35510	,
42732	,
8352	,
14427	,
34660	,
29356	,
6449	,
8317	,
26587	,
12495	,
30385	,
32167	,
19316	,
23571	,
9974	,
62664	,
30546	,
17791	,
38804	,
10586	,
28548	,
18367	,
34207	,
20149	,
29666	,
37363	,
14688	,
27646	,
14997	,
20192	,
13491	,
6790	,
17784	,
34155	,
77306	,
135105	,
25659	,
36014	,
13091	,
15839	,
7948	,
8781	,
15443	,
7593	,
8528	,
5130	,
8674	,
6682	,
7193	,
5723	,
5192	,
2380	,
1990	,
1934	,
1104	,
1138	,
4409	,
2549	,
7873	,
5291	,
1148	,
3860	,
8728	,
6867	,
7931	,
4789	,
10463	,
13903	,
4912	,
7655	,
3205	,
9093	,
11603	,
8912	,
14509	,
3479	,
4899	,
17004	,
28217	,
13876	,
9681	,
15584	,
10222	,
7544	,
24486	,
12036	,
18714	,
4668	,
13716	,
10556	,
14102	,
1736	,
6213	,
3915	,
7283	,
4289	,
13970	,
7879	,
16147	,
5496	,
2924	,
5856	,
3774	,
2541	,
2209	,
1138	,
6789	,
9169	,
1806	,
5386	,
1148	,
3599	,
4814	,
5917	,
4537	,
2977	,
4263	,
8777	,
6554	,
6212	,
1917	,
5821	,
12186	,
4829	,
557	,
10421	,
4358	,
1768	,
5849	,
6866	,
1019	,
4213	,
4762	,
2334	,
5382	,
8752	,
5819	,
3040	,
4223	,
1604	,
7756	,
6355	,
17364	,
12351	,
6885	,
5325	,
6166	,
9146	,
1505	,
8693	,
9909	,
7506	,
1147	,
3073	,
4273	,
3595	,
2548	,
2102
}
//pattern 2
,{
}
//pattern 3
, {}
//pattern 4
, {}
//pattern 5
, {}
//pattern 6
, {}
//pattern 7
, {}
//pattern 8
, {}
//pattern 9
, {}
//pattern 10
, {}
};

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
	// pattern number
	

	//txt class definition
	txt_file_class text1,text2;
	text1.txt_file_name = "input_normalized1.txt";
	text2.txt_file_name = "input_normalized2.txt";
	text1.create_textfile();
	text2.create_textfile();

	//Read a wav file
	RW_wav wav1, wav2;
	wav1.wav_name = "1_halfsecond.wav";
	wav2.wav_name = "2_halfsecond.wav";
	
	wav1.read_wav();
	wav2.read_wav();
	//printf("%d %d \n", wav1.wav_data_size, wav2.wav_data_size);

	

	//Control Parameters
	int file_header = 50;
	int data_size = 488; //must larger than 250
	//double spetrum_sum(0);
	int data_sampling_rate = 44100;
	//int delta_i(0);

	glass_broken_alert_R1 fft1, fft2;
	fft1.input_data_size = data_size;
	fft2.input_data_size = data_size;
	fft1.fft_array_initial();
	fft2.fft_array_initial();
	
	//Check the pattern sampling rate
	/*
	int pattern_sampling_rate1(0), pattern_sampling_rate2(0);
	pattern_sampling_rate1 = data_size * 44100 / (wav1.short_data_size - 50);
	printf("data_size: %d\nPattern Sampling Rate: %dHz\n", wav1.short_data_size - 50, pattern_sampling_rate1);
	//
	pattern_sampling_rate2 = data_size * 44100 / (wav2.short_data_size - 50);
	printf("data_size: %d\nPattern Sampling Rate: %dHz\n", wav2.short_data_size - 50, pattern_sampling_rate2);
	*/

	//Choice the shortest data size to be algorithm size
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
	
	

	//FFT G and H
	fft1.FFT_2_radix(); //Get G
	fft2.FFT_2_radix(); //Get H
	double calculating_buffer1(0), calculating_buffer2(0), calculating_buffer3(0);
	double calculating_buffer4(0);
	/**/
	for (int i(0); i < (data_size/2); i++)
	{
		//calculating_buffer1 = calculating_buffer1 + fft1.output_data_Amplitude[i] * fft1.output_data_Amplitude[i]; 
		//calculating_buffer2 = calculating_buffer2 + fft2.output_data_Amplitude[i] * fft2.output_data_Amplitude[i]; 
		//calculating_buffer3 = calculating_buffer3 + fft1.output_data_Amplitude[i] * fft2.output_data_Amplitude[i];
		
		printf("%f\n", fft1.output_data_Amplitude[i]); //show G
		//printf("%f\n", fft2.output_data_Amplitude[i]); //show H
		//printf("%f\n", fft1.output_data_Amplitude[i]*fft2.output_data_Amplitude[i]); //show GxH
		//printf("%f\n", fft1.output_data_Amplitude[i] - fft2.output_data_Amplitude[i]); //show GxH
		
		//text1.writing_data = fft1.output_data_Amplitude[i];
		//text2.writing_data = fft2.output_data_Amplitude[i];
		//text1.write_number_data_into_txt();
		//text2.write_number_data_into_txt();
		
		//20190615 new method
		if (fft1.output_data_Amplitude[i] > fft2.output_data_Amplitude[i])
			fft1.output_data_Amplitude[i] = fft2.output_data_Amplitude[i];
		if(fft1.output_data_Amplitude[i]>100000)
		{
			//printf("%d  %f\n",i, fft1.output_data_Amplitude[i]);
			//printf("%f\n", fft1.output_data_Amplitude[i]);
		}
		
	}


	//test
	/**/
	printf("\n\n\n\n");
	for (int i(0); i < (data_size / 2); i++)
	{
		
		printf("%f\n", fft2.output_data_Amplitude[i]); //show h
		
	}
	

	//Normalization
	//calculating_buffer1 = calculating_buffer1 / data_size ;
	//calculating_buffer2 = calculating_buffer2 / data_size ;
	//calculating_buffer3 = calculating_buffer3 / data_size ;
	//
	//printf("calculating_buffer1: %f\n", calculating_buffer1); 
	//printf("calculating_buffer2: %f\n", calculating_buffer2); 
	//printf("calculating_buffer3: %f\n", calculating_buffer3);

 	system("Pause");
	return 0;
}