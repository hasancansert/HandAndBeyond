/*
 * EMGDriver.h
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */
#pragma once
#ifndef SRC_EMGDRIVER_EMGDRIVER_H_
#define SRC_EMGDRIVER_EMGDRIVER_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "math.h"
#include "stdlib.h"


#define SAMPLE_FREQUENCY_HZ 1000		// Sampling frequency(Hz)
//const int 	Ts = 1e6/Fs;	// Sampling period (us)
#define SAMPLE_PERIOD  1e3/SAMPLE_FREQUENCY_HZ	// Sampling period (us)
#define THRESHOLD_AVARAGE_UPPER_LIMIT 80 //If noise is detected as hand movements increase this threshold. If hand movements are not detected decrease it.
#define THRESHOLD_AVARAGE_LOWER_LIMIT 50

typedef struct S_ADCConfig {
	uint8_t adc_bits; 		// The resolution of your MCU's ADC
	uint8_t default_bits;	// Don't change!
	float vref;				// Reference voltage of MCU's ADC (V)
	float default_vref;		// Default reference voltage of the Arduino Uno (V) Don't Change
	float adc_scale; 		// Scales the input signal
	float emg_offset; 		// DC offset of the Mam Sense Board EMG output. (V)
	float sig_offset;
} S_ADCConfig;

typedef struct S_FilterConfig {
	uint16_t f0;      // Cut-off frequency of the notch filter(Hz).
	uint16_t f1;     // Second cut-off frequency(Hz). (Must be integer multiple of f0)
	float w0;  // Digital cut-off frequency (rad/sample)
	float w1;  //
	float p;     //Quailty factor. Must be between 0.8 and 0.995. Default value: 0.95

	float mag; // Find magnitude of the filter at w=0 to set the DC gain to 1;

	//Create the coefficient matrices for notch filter at f0
	float num[3];
	float den[3];

	//Optional dual frequency notch filter. Comment this code block out to use dual frequency notch filter
	// Create the coefficient matrices for notch filter at f1
	float mag2;
	float num2[3];
	float den2[3];

	//Convolve two filters to obtain dual notch filter at frequencies f0 and f1
	float num3[5];
	float den3[5];

} S_FilterConfig;


static uint32_t start_time=0;
static uint32_t current_time=0;
static int16_t raw[100] =  {0};
static int16_t emg[100] = {0};
static uint32_t count=4;
static uint16_t command_counter=0;

static float curr_avg,prev_avg; // Variables to store current and previous average
static const float alpha = 0.1;  // Moving average coefficient. If hand movements are not detected change this number.
static const float prev_alpha = 1 - alpha;


void EmgConfigInit(void);
void EmgTaskFunction(void * argument);
void EmgTaskInit(void);
void EmgNotchFilter(int16_t *raw, int16_t *emg);

#endif /* SRC_EMGDRIVER_EMGDRIVER_H_ */
