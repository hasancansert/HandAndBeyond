/*
 * EMGDriver.c
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */


#include "EMGDriver.h"

TaskHandle_t emgTaskHandle;

/* USER CODE BEGIN Header_EMGTask */
/**
* @brief Function implementing the EMGTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MotorTask */
void EmgTaskFunction(void const * argument)
{
  /* USER CODE BEGIN MotorTask */
  /* Infinite loop */
  for(;;)
  {
   // HAL_UART_Transmit(&huart6, buffer, 5, HAL_MAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  /* USER CODE END MotorTask */
}

void EmgTaskInit(void)
{
	  TaskFunction_t EmgTask = EmgTaskFunction;
	  xTaskCreate(	EmgTask,
					"EMG Task",
					128,
					0,
					tskIDLE_PRIORITY,
	  				emgTaskHandle );
}
