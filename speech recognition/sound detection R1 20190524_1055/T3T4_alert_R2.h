#pragma once


//sound detection R1 20190524_1055

/*
# Some of variences are int type.
# Create a class, inclueds sine and cosine table,
SQRT(), FFT-radix-2
# Sine and Cosine table
# Iterative SQRT
# Adding #define angle2radian 57.29.
# Warming: the size of buffer, maybe over the limit of int type.
*/
#include <fstream>
#include <time.h> //for time()
#include <vector> //for vector

#define PI 3.14159
#define angle2radian 57.29 //360/(2*3.14)

class glass_broken_alert_R1
{
public:
	//FFT input setting
	int fft_start_flag, fft_end_flag;
	int sampling_rate;
	int input_data_size;
	//FFT middle array
	short* input_t_data;
	short* w_array;
	short* output_data_Amplitude;
	short output_re;
	short output_im;
	float* spectrum_x_axis;
	//Alert identity
	bool audio_alert_flag;
	short buffer_frequency_variance;
	short buffer_frequency_variance_threshold;
	short buffer_reference_frequency; 
	double max_buffer_amplitude_value;
	float buffer_amplitude_threshold_rate;
	float buffer_amplitude_threshold;
	//
	float cos_table(int input_value);
	float sin_table(int input_value);
	int sqrt_Iterative(float input_value);
	//
	void glass_broken_detection();
	void FFT_2_radix();
	void fft_x_axis();
	void fft_array_initial();
	void alert_initial();
	//sound detection
	float intergral_fft;

	glass_broken_alert_R1();
	~glass_broken_alert_R1();
};

