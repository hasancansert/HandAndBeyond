/*
 * MotorDriver.c
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */


#include "MotorDriver.h"

TaskHandle_t motorTaskHandle;

/* USER CODE BEGIN Header_MotorTask */
/**
* @brief Function implementing the motorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MotorTask */
void MotorTaskFunction(void const * argument)
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

void MotorTaskInit(void)
{
	  TaskFunction_t MotorTask = MotorTaskFunction;
	  xTaskCreate(	MotorTask,
					"Motor Task",
					128,
					0,
					tskIDLE_PRIORITY,
	  				motorTaskHandle );
}


