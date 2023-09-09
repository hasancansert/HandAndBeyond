/*
 * task_init.c
 *
 *  Created on: 8 Eyl 2023
 *      Author: ogulc
 */

#include "main.h"
#include "cmsis_os.h"
#include "motor_driver.h"
#include "task.h"
#include "task_init.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"

//UART_HandleTypeDef huart6;

/*Initializing all tasks*/
void Task_Init(void){


	MotorControl_Task_Init();

}

void MotorControl_Task_Init(void){
	TaskHandle_t task1_handle;

	/*Address of the movement detector variable, init 0 for example*/
	void *pvparameter = 0;

	BaseType_t status;

	status = xTaskCreate(MotorControlTask,
						 "Motor Control Task",
						 configMINIMAL_STACK_SIZE,
						 pvparameter,
						 3,
						 &task1_handle);
	configASSERT(status = pdPASS);

}

void MotorControlTask(void *params)
{
	uint8_t movement_detect = &params;

	uint8_t tx_buffer[8];


	/*Setting the speed of the servo motors*/
	int counter = 0;
	while(counter <= CHANNEL_4){
		Set_Speed(tx_buffer, counter);
		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	}

	switch(movement_detect){
		case fist:
		    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	        Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			break;

		case okay_sign:
	        Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			break;

		case peace_sign:
		    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			break;
		case pointing:
		    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			break;

		case good_sign:
	        Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
			HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
			break;
	}
  for(;;)
  {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(500);

		  Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  Set_Speed(tx_buffer, CHANNEL_0);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  Set_Speed(tx_buffer, CHANNEL_0);

		  Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  Set_Speed(tx_buffer, CHANNEL_1);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  Set_Speed(tx_buffer, CHANNEL_2);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

//		  Set_Target(tx_buffer, CHANNEL_3, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//		  Set_Speed(tx_buffer, CHANNEL_3);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  Set_Speed(tx_buffer, CHANNEL_4);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		  HAL_Delay(1000);
		  /*0b0000011101101000*/
		  Set_Target(tx_buffer, CHANNEL_0, TARGET_MIN_LOW, TARGET_MIN_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  Set_Target(tx_buffer, CHANNEL_1, TARGET_MAX_LOW, TARGET_MAX_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  Set_Target(tx_buffer, CHANNEL_2, TARGET_MIN_LOW, TARGET_MIN_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

//		  Set_Target(tx_buffer, CHANNEL_3, TARGET_MIN_LOW, TARGET_MIN_HIGH);
//		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  Set_Target(tx_buffer, CHANNEL_4, TARGET_MIN_LOW, TARGET_MIN_HIGH);
		  HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);

		  /* USER CODE END 2 */
		  HAL_Delay(1000);
  }
  /* USER CODE END 5 */
}

