#pragma once


//FFT 2Radix_DIT_Complex_Characteristics R6 20190605_1452

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
	long check_nk;
	int Radix2_nk, Radix2_k;
	short Radix2_sign_flag;
	//double ffr_value_buffer;
	//short sign_flag;
	//FFT middle array
	short* input_t_data;
	double* w_array_cos, * w_array_sin;
	double* output_data_Amplitude;
	double output_re, output_im, output_re2, output_im2,output_buffer;
	float* spectrum_x_axis;

	//
	float cos_table(int input_value);
	float sin_table(int input_value);
	int sqrt_Iterative(float input_value);
	//
	void glass_broken_detection();
	void fft_2_Radix_initial();
	void FFT_2_radix();
	void fft_x_axis();
	void fft_complex_characteristic_initial();
	void FFT_complex_characteristic();

	glass_broken_alert_R1();
	~glass_broken_alert_R1();
};

