

//glassBrokenDetection R13 20190702_1505

/**/
#include <fstream>
#include <time.h> //for time()
#include <vector> //read folder
#include <Windows.h> //read folder, system("PAUSE")
#include <math.h>

#define PI 3.14159


int positiveNumber(0), falesNumber(0);
bool positiveFlag(0);
int fileName(0);

//Read a folder
/*
input:
firstFileName
(specific file end, ex: .wav) unfinished

output:
folderList
fileList
folderList.size()
fileList.size()

*/
class Read_folder
{
public:
	std::string firstFileName;
	std::string str, pattern, filename;
	std::vector<std::string> folderList, fileList;
	std::vector<std::string> fileNmaeCheckResult;
	Read_folder();
	//~Read_folder();
	void StrSplit();
	void GetFileNameListInDir();
	void main();
};
Read_folder::Read_folder()
{
}
void Read_folder::StrSplit()
{
	std::string::size_type pos;

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
				fileNmaeCheckResult.push_back(s);
			}
			i = pos + pattern.size() - 1;
		}
	}

}
void Read_folder::GetFileNameListInDir()
{
	short buffer1(0);
	//windows x64
	std::string search_path = firstFileName + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) //is fd not a folder? (is file)
			{
				filename = fd.cFileName;// FindFileData.cFileName;
				//For StrSplit()
				str = filename;
				pattern = ".";
				StrSplit();
				str = fileNmaeCheckResult[fileNmaeCheckResult.size() - 1];

				//
				/**/
				if (("raw" == str || "RAW" == str || "wav" == str || "WAV" == str))
				{

					filename = firstFileName + "/" + filename;
					fileList.push_back(filename);
				}

				//nameList.push_back(fd.cFileName);


			}
			else //detecting the names of folder
			{

				//test 20190619
				filename = fd.cFileName;// FindFileData.cFileName;
				filename = firstFileName + "/" + filename;
				//std::cout << vecImages.size() << std::endl;
				//folderList.push_back(filename);
				//printf("%s\n", fd.cFileName);
				if (buffer1 < 2)
				{
					buffer1++;
				}
				else
				{
					folderList.push_back(filename);
					//folderNumber++;
				}

			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	//return nameList;
}
void Read_folder::main()
{
	//int allFolderNumber(0);

	for (int i(0);; i++)
	{
		if (i == 0)
		{
			folderList.push_back(firstFileName);
			//printf("%s\n", folderList[i].c_str());
			firstFileName = folderList[0];
			GetFileNameListInDir();
			//printf("%s\n", folderList[i].c_str());
		}
		else
		{
			firstFileName = folderList[i];
			GetFileNameListInDir();
			//printf("%s\n", folderList[i].c_str());
		}
		//allFolderNumber =allFolderNumber + folderNumber; 
		//allFileNumber = allFileNumber + fileNumber;
		//printf("%d %d\n", i,folderList.size());
		if (i == folderList.size() - 1)  // After read the last folder
			break;
		//if (i == allFolderNumber)  // After read the last folder 
		//	break;
	}
}

//T3T4
class T3T4_alert_R2
{
public:
	//FFT input setting
	//int fft_start_flag, fft_end_flag;
	int sampling_rate;
	//int max_output_data;
	//int buffer1;
	//int input_data_size;
	//FFT middle array
	//short* input_t_data;
	//double* w_array;
	//double* output_data_Amplitude;
	//double output_re;
	//double output_im;
	float* spectrum_x_axis;
	//
	float* re, * im;
	int data_size;
	int n, m;
	float* cost, * sint;
	float* output_data_Amplitude;
	//Alert identity
	float alert_period;
	int alertPeriodPoint, alert_counter_threshold, detectionCounter, alert_counter; //
	short alert_frequency_minimum, alert_frequency_maximum; //specific frequency
	int alert_amplitude_threshold;
	bool buffer_alert_flag;
	bool audio_alert_flag;
	//short spectrum_y_and_filter;
	//
	float cos_table(int input_value);
	float sin_table(int input_value);
	int sqrt_Iterative(float input_value);
	//
	void T3T4_detection();
	void FFT_2_radix();
	void fft_x_axis();
	void fft_array_initial();
	void alert_initial();

	T3T4_alert_R2();
	~T3T4_alert_R2();
};
T3T4_alert_R2::T3T4_alert_R2()
{
	//input_data_size = 500;
	//input_t_data = new short[input_data_size];
	alert_period = 0.8; //second
	detectionCounter = 0;
	sampling_rate = 16000;
	//max_output_data = 0;
	//
	data_size = 512;
	re = new float[data_size];
	im = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	output_data_Amplitude = new float[data_size / 2];
	//
	//alert_times_threshold = 16;
	//fft_start_flag = 0;
	//fft_end_flag = fft_start_flag + data_size;
	alert_frequency_minimum = 2800; //
	alert_frequency_maximum = 3200; //specific frequency maximum
	alert_amplitude_threshold = 1000000; //
	//
	alertPeriodPoint = alert_period * sampling_rate / data_size;
	alert_counter_threshold = alertPeriodPoint * 0.5;
	//printf("%f %d %d %d %d\n", alert_period, sampling_rate, data_size, alertPeriodPoint, alert_counter_threshold);
}
void T3T4_alert_R2::alert_initial()
{
	alert_counter = alert_period * 0.8;
	buffer_alert_flag = 0;
	audio_alert_flag = 0;
	//detectionCounter = 0;
}
//initial the arraies in FFT radix 2 Algorithm
void T3T4_alert_R2::fft_array_initial()
{
	//
	alertPeriodPoint = alert_period * sampling_rate / data_size;
	alert_counter_threshold = alertPeriodPoint * 0.5;
	//printf("%f %d %d %d %d\n", alert_period, sampling_rate, data_size, alertPeriodPoint, alert_counter_threshold);

	//w_array = new double[input_data_size];
	//output_data_Amplitude = new double[input_data_size];
	spectrum_x_axis = new float[data_size];
	//
	delete re, im, cost, sint, output_data_Amplitude;
	re = new float[data_size];
	im = new float[data_size];
	output_data_Amplitude = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	n = data_size;
	m = log(data_size) / log(2);
	//printf("%d\n", m);
	float base(0);
	for (int i = 0; i < data_size / 2; i++)
	{
		base = -2 * PI * i / data_size;
		cost[i] = cos(base);
		sint[i] = sin(base);
	}
}
//FFT spectrum x axis
void T3T4_alert_R2::fft_x_axis()
{
	for (int i(0); i < data_size; i++)
	{
		spectrum_x_axis[i] = i * sampling_rate / data_size;
	}
}
//FFT radix 2 Algorithm
void T3T4_alert_R2::FFT_2_radix()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int n1 = 0;
	int n2 = 0;
	int a = 0;

	float cos = 0;
	float sin = 0;
	float t1 = 0;
	float t2 = 0;

	// Bit-reverse
	n2 = n / 2;

	for (i = 1; i < n - 1; i++)
	{

		n1 = n2;
		while (j >= n1)
		{
			j = j - n1;
			n1 = n1 / 2;
		}
		j = j + n1;
		if (i < j)
		{
			t1 = re[i];
			re[i] = re[j];
			re[j] = t1;
			t1 = im[i];
			im[i] = im[j];
			im[j] = t1;
		}
	}

	// FFT
	n1 = 0;
	n2 = 1;

	for (i = 0; i < m; i++)
	{
		n1 = n2;
		n2 = n2 + n2;
		a = 0;

		for (j = 0; j < n1; j++)
		{
			cos = cost[a];
			sin = sint[a];
			for (k = j; k < n; k = k + n2)
			{
				t1 = cos * re[k + n1] - sin * im[k + n1];
				t2 = sin * re[k + n1] + cos * im[k + n1];
				re[k + n1] = re[k] - t1;
				im[k + n1] = im[k] - t2;
				re[k] = re[k] + t1;
				im[k] = im[k] + t2;
				//printf("%f %f \n", t1,t2);
				//printf("i=%d j=%d k=%d a=%d\n", i, j, k, a);
			}
			a += 1 << (m - i - 1);
		}
	}
	//To get the absolute value of complex number
	for (int g = 0; g < data_size; g++)
	{
		output_data_Amplitude[g] = sqrt(re[g] * re[g] + im[g] * im[g]);
		//printf("%f \n", output_data_Amplitude[g]);
	}
}
//T3T4_detection
void T3T4_alert_R2::T3T4_detection()
{
	//Show the start and end flag
	//printf("%d %d %f %f\n",fft_start_flag, fft_end_flag, float(fft_start_flag/16000), float(fft_end_flag / 16000));
	//buffer1 = alert_amplitude_threshold * 0.3;

	alert_amplitude_threshold = 1000000;
	//alert_times_threshold = 8;
	if (detectionCounter > 0)
	{
		detectionCounter++;
	}
	buffer_alert_flag = 0;
	//printf("\n");
	for (int i(0); i < data_size / 2; i++)
	{
		//test 20190621
		/**/
		if (output_data_Amplitude[i] > alert_amplitude_threshold)
		{
			//printf("%f\n", spectrum_x_axis[i]);
			//printf("%f\n", spectrum_x_axis[i]);
			//printf("%d %f %f\n", alert_amplitude_threshold, spectrum_x_axis[i], output_data_Amplitude[i]);
			if ((spectrum_x_axis[i] > alert_frequency_minimum) && (spectrum_x_axis[i] < alert_frequency_maximum))
			{
				//printf("%d %f %f %d %d\n", alert_amplitude_threshold, spectrum_x_axis[i], output_data_Amplitude[i], detectionCounter, alert_counter);
				//printf("%d %d\n", detectionCounter, alert_counter);
				buffer_alert_flag = 1;
				//break;
				//break;
			}
			if ((spectrum_x_axis[i] > alert_frequency_maximum))
			{
				//printf("%d %f %f %d\n", alert_amplitude_threshold, spectrum_x_axis[i], output_data_Amplitude[i], alert_counter);
				buffer_alert_flag = 0;
				alert_counter = 0;
				//break;
			}
		}

	}
	//printf("%d %d\n", detectionCounter, alert_counter);
	//test
	//printf("%d\n", buffer2);
	//buffer2 = 0;
	if (buffer_alert_flag == 1)
	{
		buffer_alert_flag = 0;
		alert_counter++;
		if (alert_counter == 1)
		{
			detectionCounter = 1;
		}

	}
	if (detectionCounter > alertPeriodPoint)
	{
		alert_counter = 0;
		detectionCounter = 0;
	}
	//Check the continuously alert
	if (alert_counter >= alert_counter_threshold)
	{
		alert_counter = 0;
		audio_alert_flag = 1;

	}
}
//SQRT
int T3T4_alert_R2::sqrt_Iterative(float input_value)
{
	double result_value(0);
	double trial_value(1);
	double check_value(0);

	for (int i(0);; i++)
	{
		result_value = 0.5 * (trial_value + input_value / trial_value);
		check_value = result_value - trial_value;
		//printf("i=%d , result_value=%f\n", i, result_value); //check the each result
		//printf("i=%d , result_value=%f\n", i, check_value); // check the each delt_value

		if (check_value < 0)
		{
			check_value = -check_value;
		}

		if (check_value < 0.1) //the accuracy of result
		{
			//printf("%.2lf , result_value=%f\n", input_value, result_value); // check the each delt_value
			return result_value;
			//break;
		}
		trial_value = result_value;
	}
}
//Sine_table
T3T4_alert_R2::~T3T4_alert_R2()
{
	//release the momory space
	//delete input_t_data;
	//delete w_array;
	delete output_data_Amplitude;
	delete spectrum_x_axis;

	//input_t_data = NULL;
	//w_array = NULL;
	output_data_Amplitude = NULL;
	spectrum_x_axis = NULL;
}
//Read a .wav file
class RW_wav
{
public:
	const char* wav_name;
	FILE* pFile; //file point
	long wav_data_size;  //The size of file stream
	short* wav_data_buffer; //data buffer, the wav data is 16bits, so using short type
	size_t result;
	RW_wav()
	{
		delete wav_name;
		wav_name = NULL;
		delete wav_data_buffer;
		wav_data_buffer = NULL;
	}
	void read_wav()
	{
		pFile = fopen(wav_name, "rb");
		if (pFile == NULL)
		{
			printf("%d", fileName);
			fputs("File error", stderr);
			exit(1);
		}
		//
		fseek(pFile, 0, SEEK_END); //Set the location to the end of file
		// 1 byte Size
		wav_data_size = ftell(pFile); //Returns the end-location value of the position indicator of the stream.
		//printf("wav_data_size=%d\n",wav_data_size);
		// 2 byte Size, Short Size
		wav_data_size = wav_data_size / 2;
		rewind(pFile);

		// allocate memory to contain the whole file:
		wav_data_buffer = (short*)malloc(sizeof(short) * wav_data_size*2); //set a space for buffer, buffer_size=data_type*data number
		if (wav_data_buffer == NULL) { fputs("Memory error", stderr); } //Check exit(2);

		// copy the file into the buffer:
		result = fread(wav_data_buffer,1, wav_data_size, pFile);
		//if (result != wav_data_size) { fputs("Reading error", stderr); } //Check exit(3);

		//Stereo Size
		if (wav_data_buffer[11] == 2)
		{
			wav_data_size = wav_data_size / 2;

			for (int i(22); i < wav_data_size; i++)
			{
				wav_data_buffer[i] = (wav_data_buffer[2*i]+ wav_data_buffer[2 * i])/2;
			}
		}

		//Release the file point
		fclose(pFile);
		//
		//delete wav_name;
		//wav_name = NULL;
	}
	void wavInfo();
	~RW_wav()
	{
		//delete wav_name;

		//wav_name = NULL;
		delete wav_data_buffer;
		wav_data_buffer = NULL;
	}
};
void RW_wav::wavInfo()
{
	//Stereo or Mono
	if (wav_data_buffer[11] == 1)
	{
		printf("Channel Number:%d ,Mono Audio\n", wav_data_buffer[11]);
	}
	else
	{
		printf("Channel Number:%d ,Stereo Audio\n", wav_data_buffer[11]);
	}
	//Sampling Rate
	int buffer1(0);
	if (wav_data_buffer[12] < 0) buffer1 = wav_data_buffer[12] + 65536;
	else buffer1 = wav_data_buffer[12];
	printf("sampling_rate:%d\n", buffer1); //13th is the sampling rate
	//Data Size
	printf("Data Size:%d\n", wav_data_size);
	printf("Time length: %d second\n\n", wav_data_size / buffer1);
}
//FFT 2 Radix
/**/
class FFT_2radix
{
public:
	float* re, * im;
	int data_size;
	int n, m;
	float* cost, * sint;
	float* output_data_Amplitude;
	//
	FFT_2radix();
	void FFT_2radix_initialization();
	void FFT_2radix_algorithm();
};
FFT_2radix::FFT_2radix()
{
	data_size = 512;
	re = new float[data_size];
	im = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	output_data_Amplitude = new float[data_size / 2];
}
void FFT_2radix::FFT_2radix_initialization()
{
	delete re, im, cost, sint, output_data_Amplitude;
	re = new float[data_size];
	im = new float[data_size];
	output_data_Amplitude = new float[data_size];
	cost = new float[data_size / 2];
	sint = new float[data_size / 2];
	n = data_size;
	m = log(data_size) / log(2);
	//printf("%d\n", m);
	float base(0);
	for (int i = 0; i < data_size / 2; i++)
	{
		base = -2 * PI * i / data_size;
		cost[i] = cos(base);
		sint[i] = sin(base);
	}
}
void FFT_2radix::FFT_2radix_algorithm()
{
	//printf("%d\n", data_size);
	//test
	//printf("n %d m %d\n", n, m);
	int i = 0;
	int j = 0;
	int k = 0;
	int n1 = 0;
	int n2 = 0;
	int a = 0;

	float cos = 0;
	float sin = 0;
	float t1 = 0;
	float t2 = 0;

	// Bit-reverse
	n2 = n / 2;

	for (i = 1; i < n - 1; i++)
	{

		n1 = n2;
		//printf("1 i=%d j=%d\n", i, j);
		while (j >= n1)
		{
			j = j - n1;
			n1 = n1 / 2;
			//printf("2 i=%d j=%d\n", i, j);
		}
		j = j + n1;
		if (i < j)
		{
			t1 = re[i];
			re[i] = re[j];
			re[j] = t1;
			t1 = im[i];
			im[i] = im[j];
			im[j] = t1;
			//printf("%f %f\n", re[i],im[j]);
			//printf("3 i=%d j=%d\n", i, j);
		}
	}
	//test
	/*
	for (int i(0); i < data_size ; i++)
	{
		printf("%f %f\n", re[i], im[j]);
	}
	*/

	// FFT
	n1 = 0;
	n2 = 1;

	for (i = 0; i < m; i++)
	{
		n1 = n2;
		n2 = n2 + n2;
		a = 0;

		//printf("%d\n", n1);
		for (j = 0; j < n1; j++)
		{
			cos = cost[a];
			sin = sint[a];
			//printf("%d %f %f \n",a, cost[a], sint[a]);

			//printf("i=%d j=%d k=%d a=%d\n",i,j,k, a);
			//printf("a= %d %d\n", a,j);
			//printf("\n");
			for (k = j; k < n; k = k + n2)
			{
				t1 = cos * re[k + n1] - sin * im[k + n1];
				t2 = sin * re[k + n1] + cos * im[k + n1];
				re[k + n1] = re[k] - t1;
				im[k + n1] = im[k] - t2;
				re[k] = re[k] + t1;
				im[k] = im[k] + t2;
				//printf("%f %f \n", t1,t2);
				//printf("i=%d j=%d k=%d a=%d\n", i, j, k, a);
			}
			a += 1 << (m - i - 1);
		}
	}
	//To get the absolute value of complex number
	for (int g = 0; g < data_size; g++)
	{
		output_data_Amplitude[g] = sqrt(re[g] * re[g] + im[g] * im[g]);
		//printf("%f\n", output_data_Amplitude[g]);
		//printf("%d\n", re[g]);
	}
}

//TXT file
//create a txt file
void create_textfile(const char* txt_file_name)
{
	std::ofstream txt_file;
	txt_file.open(txt_file_name, std::ios::out | std::ios::trunc);
	//Check the text file, if it is created fail, show the warming information
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	txt_file.close();
}
//write_number_data_into_txt
void write_number_data_into_txt(const char* txt_file_name, float export_txt_data)
{
	std::ofstream txt_file;
	txt_file.open(txt_file_name, std::ios::out | std::ios::app);
	if (!txt_file)
	{
		printf("Export_file is opened fail\n");
	}
	txt_file << export_txt_data << "\n";
	txt_file.close();
}


void T3T4_detection(std::string strFileName)
{

	//Read a wav file
	RW_wav wav_file_1;
	wav_file_1.wav_name = strFileName.c_str();
	wav_file_1.read_wav();
	//wav_file_1.wavInfo();


	//printf("wav_data_size = %d\n", wav_file_1.wav_data_size);
	

	//T3T4
	T3T4_alert_R2 t3t4_1;
	int buffer1(0);
	buffer1 = wav_file_1.wav_data_buffer[12];
	if (buffer1 < 0) buffer1 = buffer1 + 65536;
	t3t4_1.sampling_rate = buffer1; //16000 //44100
	//printf("sampling_rate:%d\n", t3t4_1.sampling_rate); //13th is the sampling rate

	t3t4_1.data_size = 512;
	t3t4_1.alert_amplitude_threshold = 1700000; //1000000 
	t3t4_1.alert_frequency_maximum = 3700;
	t3t4_1.alert_frequency_minimum = 2500;
	t3t4_1.alert_period = 0.8; //second
	t3t4_1.fft_array_initial();
	t3t4_1.fft_x_axis();

	//
	create_textfile("outputData.txt");
	create_textfile("inputData.txt");


	//int iWavSegmentation = wav_file_1.wav_data_size / FFT1.data_size;
	int iWavSegmentation = wav_file_1.wav_data_size / t3t4_1.data_size;

	for (int iseg = 1; iseg < iWavSegmentation; iseg++)
	{

		//Get data of the fft_buffer
		for (int i(0), j(0); i < t3t4_1.data_size; i++)
		{
			t3t4_1.re[i] = float(wav_file_1.wav_data_buffer[iseg * t3t4_1.data_size + i]);
			//t3t4_1.re[i] = float(wav_file_1.wav_data_buffer[j]);
			t3t4_1.im[i] = 0;
			//input_t_data[i] = FFT1.re[i];
			//printf("%f \n", t3t4_1.re[i]);
			//write_number_data_into_txt("inputData.txt", t3t4_1.re[i]);
		}

		t3t4_1.FFT_2_radix();
		//t3t4_1.T3T4_detection();
		
		//show the result of FFT
		/*
		for (int i(0); i < t3t4_1.data_size; i++)
		{
			//printf("%f\n", t3t4_1.output_data_Amplitude[i]);
			//write_number_data_into_txt("outputData.txt", t3t4_1.output_data_Amplitude[i]);
		}*/
		
		

		//
		if (t3t4_1.audio_alert_flag == 1)
		{
			//printf("T3T4 Alert\n");
			//printf("%s\n", strFileName.c_str());
			//t3t4_1.audio_alert_flag = 0;
			positiveNumber++;
			positiveFlag = 1;
			break;
		}
	}
}
int main()
{
	//test
	Read_folder read1;
	//read1.allFolderNumber = 0;
	//read1.allFileNumber = 0;
	read1.firstFileName = "test3";

	read1.main();
	/**/
	for (int i(0); i < read1.fileList.size(); i++)
	{
		printf("%d: %s\n", i, read1.fileList[i].c_str());
		//fileName = i;
		//printf("%s\n", read1.fileList[i].c_str());
		T3T4_detection(read1.fileList[i]);
		if (positiveFlag == 1) //if the alert occours in the audio file
		{
			//printf("%s\n", read1.fileList[i].c_str());
			positiveFlag = 0;
		}
		else //
		{
			//printf("%d\n", i);
			//printf("%s\n", read1.fileList[j].c_str());
		}
	}
	printf("positiveNumber: %d, All file number:%d", positiveNumber, read1.fileList.size());


	return 0;


	system("pause");
	return 0;
}


