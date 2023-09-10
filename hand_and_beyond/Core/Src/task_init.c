/*
 * task_init.c
 *
 *  Created on: Sep 9, 2023
 *      Author: baris
 */


#include "main.h"
#include "cmsis_os.h"
#include "MotorDriver.h"
#include "EMGDriver.h"
#include "task.h"
#include "semphr.h"
#include "task_init.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"

//UART_HandleTypeDef huart6;
//TaskHandle_t emgTaskHandle;

/*Initializing all tasks*/
//void Task_Init(void){
//
//
//	MotorControl_Task_Init();
////	EmgTaskInit();
//
//}
//
//void MotorControl_Task_Init(void){
//
//	TaskHandle_t task1_handle;
//
//	BaseType_t status;
//
//	status = xTaskCreate(MotorControlTask,
//						 "Motor Control Task",
//						 configMINIMAL_STACK_SIZE,
//						 NULL,
//						 tskIDLE_PRIORITY + 1,
//						 &task1_handle);
//	configASSERT(status = pdPASS);
//
//}
//
//void MotorControlTask(void *params)
//{
//	uint8_t movement_detect = 0;
//
//	uint8_t tx_buffer[8];
//
//
//	/*Setting the speed of the servo motors*/
//	int counter = 0;
//	while(counter <= CHANNEL_4){
//		Set_Speed(tx_buffer, counter);
//		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		counter++;
//	}
//
//
//  for(;;)
//  {
//	  xSemaphoreTake(handFlexHandle, portMAX_DELAY);
//
//		switch(movement_detect){
//			case fist:
//			    Set_Target(tx_buffer, CHANNEL_0, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//			  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		        Set_Target(tx_buffer, CHANNEL_1, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_2, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_4, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				break;
//
//			case okay_sign:
//		        Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				break;
//
//			case peace_sign:
//			    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//			  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				break;
//			case pointing:
//			    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//			  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				break;
//
//			case good_sign:
//		        Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//				HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//				break;
//		}
//
//		xSemaphoreTake(handReleaseHandle, portMAX_DELAY);
//
//		Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//
//  }
//  /* USER CODE END 5 */
//}

//void EmgTaskFunction(void * argument)
//{
////	TickType_t xLastWakeTime;
////	const TickType_t xSamplingPeriod = pdMS_TO_TICKS(1000 / SAMPLE_FREQUENCY_HZ);
////
////	xLastWakeTime = xTaskGetTickCount();
//
//  /* USER CODE BEGIN MotorTask */
//  /* Infinite loop */
//  for(;;)
//  {
//
////	  HAL_ADC_Start(&hadc1);
////	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
////	  raw[count%100] = round( HAL_ADC_GetValue(&hadc1)*ADC_Config.adc_scale-ADC_Config.sig_offset);
////
////	  vTaskDelayUntil(&xLastWakeTime, xSamplingPeriod);
////
////	  EmgNotchFilter(raw, emg);
//
//	  current_time = HAL_GetTick();
//
//	  if(current_time - start_time >= SAMPLE_PERIOD)
//	  {
//		  start_time = current_time;
//
//		  HAL_ADC_Start(&hadc1);
//		  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
////		  raw[count%100] = round( HAL_ADC_GetValue(&hadc1)*ADC_Config.adc_scale-ADC_Config.sig_offset);
//		  raw[count%100] = HAL_ADC_GetValue(&hadc1);
////		  printf("raw = %d\n",emg[count%100]);
//
//		  EmgNotchFilter(raw, emg);
//
//		  curr_avg = abs(emg[count%100])*alpha + prev_avg*prev_alpha;  //Calculate the current average.
//		  prev_avg=curr_avg;
//
////		  printf("filtered = %d\n",emg[count%100]);
//
////		  if(command_counter>0){
////			command_counter--;
////			if(command_counter==0){
////			  xSemaphoreGive(handReleaseHandle);
////			}
////		  }
//
//		  if(abs(emg[count%100]) - prev_avg <= THRESHOLD_AVARAGE_LOWER_LIMIT)
//		  {
//			  xSemaphoreGive(handReleaseHandle);
//		  }
//
//		  if(abs(emg[count%100]) - prev_avg >= THRESHOLD_AVARAGE_UPPER_LIMIT){
//			  xSemaphoreGive(handFlexHandle);
////			if(command_counter==0){
////			 xSemaphoreGive(handFlexHandle);
////			}
////			command_counter = SAMPLE_FREQUENCY_HZ / 4;
//		  }
//		  count++;
//	  }
//  }
//  /* USER CODE END MotorTask */
//}
//
//void EmgTaskInit(void)
//{
//	  TaskFunction_t EmgTask = EmgTaskFunction;
//	  xTaskCreate(	EmgTask,
//					"EMG Task",
//					128,
//					NULL,//(void *) &hadc1
//					tskIDLE_PRIORITY + 1,
//	  				emgTaskHandle );
//}
