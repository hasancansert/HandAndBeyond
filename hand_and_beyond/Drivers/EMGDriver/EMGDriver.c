/*
 * EMGDriver.c
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */

#include "EMGDriver.h"


TaskHandle_t emgTaskHandle;

S_ADCConfig ADC_Config;
S_FilterConfig Filter_Config;

void EmgConfigInit(void){

	//ADC configuration
	ADC_Config.default_bits = 10; // Don't change!
	ADC_Config.adc_bits = 10; // The resolution of your MCU's ADC
	ADC_Config.vref = 3.3f; // Reference voltage of MCU's ADC (V)
	ADC_Config.default_vref = 5 ;// Default reference voltage of the Arduino Uno (V) Don't Change
	ADC_Config.adc_scale = pow(2,ADC_Config.default_bits-ADC_Config.adc_bits)*ADC_Config.vref/ADC_Config.default_vref; // Scales the input signal
	ADC_Config.emg_offset = 1.45; // DC offset of the Mam Sense Board EMG output. (V)
	ADC_Config.sig_offset = round(pow(2,ADC_Config.default_bits)*ADC_Config.emg_offset/ADC_Config.default_vref);

	Filter_Config.f0 = 50;      // Cut-off frequency of the notch filter(Hz).
	Filter_Config.f1 = 150;     // Second cut-off frequency(Hz). (Must be integer multiple of f0)
	Filter_Config.w0 = 2*3.1416*Filter_Config.f0/SAMPLE_FREQUENCY_HZ;  // Digital cut-off frequency (rad/sample)
	Filter_Config.w1 = 2*3.1416*Filter_Config.f1/SAMPLE_FREQUENCY_HZ;  //
	Filter_Config.p = 0.95;     //Quailty factor. Must be between 0.8 and 0.995. Default value: 0.95

	Filter_Config.mag = (1 -2*cos(Filter_Config.w0) +1)/(1 -2*Filter_Config.p*cos(Filter_Config.w0) + Filter_Config.p*Filter_Config.p); // Find magnitude of the filter at w=0 to set the DC gain to 1;

	//Create the coefficient matrices for notch filter at f0
	Filter_Config.num[0] = 1.0 / Filter_Config.mag;
	Filter_Config.num[1] = -2.0 * cos(Filter_Config.w0) / Filter_Config.mag;
	Filter_Config.num[2] = 1.0 / Filter_Config.mag;

	Filter_Config.den[0] = 1;
	Filter_Config.den[1] = -2 * Filter_Config.p * cos(Filter_Config.w0);
	Filter_Config.den[2] = Filter_Config.p * Filter_Config.p;

	//Optional dual frequency notch filter. Comment this code block out to use dual frequency notch filter
	// Create the coefficient matrices for notch filter at f1
	Filter_Config.mag2 = (1 -2*cos(Filter_Config.w1) +1)/(1 -2*Filter_Config.p*cos(Filter_Config.w1) + Filter_Config.p*Filter_Config.p);

	Filter_Config.num2[0] = 1.0 / Filter_Config.mag2;
	Filter_Config.num2[1] = -2.0 * cos(Filter_Config.w1) / Filter_Config.mag2;
	Filter_Config.num2[2] = 1.0 / Filter_Config.mag2;

	Filter_Config.den2[0] = 1;
	Filter_Config.den2[1] = -2 * Filter_Config.p * cos(Filter_Config.w1);
	Filter_Config.den2[2] = Filter_Config.p * Filter_Config.p;

	//Convolve two filters to obtain dual notch filter at frequencies f0 and f1
	Filter_Config.num3[0] = Filter_Config.num[0] * Filter_Config.num2[0];
	Filter_Config.num3[1] = Filter_Config.num2[0] * Filter_Config.num[1] + Filter_Config.num2[1] * Filter_Config.num[0];
	Filter_Config.num3[2] = Filter_Config.num2[0] * Filter_Config.num[2] + Filter_Config.num2[1] * Filter_Config.num[1] + Filter_Config.num2[2] * Filter_Config.num[0];
	Filter_Config.num3[3] = Filter_Config.num2[1] * Filter_Config.num[2] + Filter_Config.num2[2] * Filter_Config.num[1];
	Filter_Config.num3[4] = Filter_Config.num2[2] * Filter_Config.num[2];

	Filter_Config.den3[0] = 1;
	Filter_Config.den3[1] = Filter_Config.den2[0] * Filter_Config.den[1] + Filter_Config.den2[1] * Filter_Config.den[0];
	Filter_Config.den3[2] = Filter_Config.den2[0] * Filter_Config.den[2] + Filter_Config.den2[1] * Filter_Config.den[1] + Filter_Config.den2[2] * Filter_Config.den[0];
	Filter_Config.den3[3] = Filter_Config.den2[1] * Filter_Config.den[2] + Filter_Config.den2[2] * Filter_Config.den[1];
	Filter_Config.den3[4] = Filter_Config.den2[2] * Filter_Config.den[2];

}


/**
* @brief Function implementing the EMGTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MotorTask */
void EmgTaskFunction(void * argument)
{
//	TickType_t xLastWakeTime;
//	const TickType_t xSamplingPeriod = pdMS_TO_TICKS(1000 / SAMPLE_FREQUENCY_HZ);
//
//	xLastWakeTime = xTaskGetTickCount();

  /* USER CODE BEGIN MotorTask */
  /* Infinite loop */
  for(;;)
  {

//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
//	  raw[count%100] = round( HAL_ADC_GetValue(&hadc1)*ADC_Config.adc_scale-ADC_Config.sig_offset);
//
//	  vTaskDelayUntil(&xLastWakeTime, xSamplingPeriod);
//
//	  EmgNotchFilter(raw, emg);

	  current_time = HAL_GetTick();

	  if(current_time - start_time >= SAMPLE_PERIOD)
	  {
		  start_time = current_time;

		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		  raw[count%100] = round( HAL_ADC_GetValue(&hadc1)*ADC_Config.adc_scale-ADC_Config.sig_offset);
//		  raw[count%100] = HAL_ADC_GetValue(&hadc1);
//		  printf("raw = %d\n",emg[count%100]);

		  EmgNotchFilter(raw, emg);

		  curr_avg = abs(emg[count%100])*alpha + prev_avg*prev_alpha;  //Calculate the current average.

		  prev_avg=curr_avg;

//		  printf("filtered = %d\n",emg[count%100]);

		  if(command_counter>0){
			command_counter--;
			if(command_counter==0){
			  xSemaphoreGive(handReleaseHandle);
			}
		  }

		  if(abs(emg[count%100]) - prev_avg >= THRESHOLD_AVARAGE_UPPER_LIMIT){
			if(command_counter==0){
			 xSemaphoreGive(handFlexHandle);
			}
			command_counter = SAMPLE_FREQUENCY_HZ;
		  }
		  count++;
	  }
  }
  /* USER CODE END MotorTask */
}

void EmgTaskInit(void)
{
	  TaskFunction_t EmgTask = EmgTaskFunction;
	  xTaskCreate(	EmgTask,
					"EMG Task",
					128,
					NULL,//(void *) &hadc1
					tskIDLE_PRIORITY,
	  				emgTaskHandle );
}

void EmgNotchFilter(int16_t *raw, int16_t *emg)
{
	emg[count%100] = round(raw[count%100]*Filter_Config.num[0] + raw[(count-1)%100]*Filter_Config.num[1] + raw[(count-2)%100]*Filter_Config.num[2] - emg[(count-1)%100]*Filter_Config.den[1] - emg[(count-2)%100]*Filter_Config.den[2]);

}

//void ADC_Task(void *pvParameters) {
//    uint8_t channel = 0; // Initialize with the first channel
//
//    while (1) {
//        // Configure the multiplexer to select the current channel
//        // Adjust this part according to your hardware setup
//        // For example, if you're using GPIO pins to control the multiplexer, set them here
//
//
//    	taskENTER_CRITICAL();
//
//        // Start the ADC conversion
//        HAL_ADC_Start(&hadc1);
//
//        // Wait for the conversion to complete
//        if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK) {
//            // Read the ADC value and store it in the buffer
//            adcValues[channel] = HAL_ADC_GetValue(&hadc1);
//        }
//
//        // Stop the ADC conversion
//        HAL_ADC_Stop(&hadc1);
//
//        taskEXIT_CRITICAL();
//
//        // Delay to achieve a 1 kHz sampling rate
//        vTaskDelay(pdMS_TO_TICKS(1));
//
//        // Increment the channel and wrap around if needed
//        channel = (channel + 1) % NUM_CHANNELS;
//    }
//}

