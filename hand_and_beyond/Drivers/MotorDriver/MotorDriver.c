/*
 * MotorDriver.c
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */

#include "main.h"
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
	uint32_t movement_detect = (uint32_t) argument;

	uint8_t tx_buffer[8];

	/*Setting the speed of the servo motors*/
	int counter = 0;
	while(counter <= CHANNEL_4){
		Set_Speed(tx_buffer, counter);
		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
		counter++;
	}

	/* Infinite loop */

	for(;;)
	{
//		xSemaphoreTake(handFlexHandle, portMAX_DELAY);
//		// HAL_UART_Transmit(&huart6, buffer, 5, HAL_MAX_DELAY);
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND FLEXED @@@@@@@@@@@@@@@@@@@@@@@@\n");
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND FLEXED @@@@@@@@@@@@@@@@@@@@@@@@\n");
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND FLEXED @@@@@@@@@@@@@@@@@@@@@@@@\n");
//		xSemaphoreTake(handReleaseHandle, portMAX_DELAY);
//		// HAL_UART_Transmit(&huart6, buffer, 5, HAL_MAX_DELAY);
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND RELEASED @@@@@@@@@@@@@@@@@@@@@@@@\n");
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND RELEASED @@@@@@@@@@@@@@@@@@@@@@@@\n");
//		printf("@@@@@@@@@@@@@@@@@@@@ HAND RELEASED @@@@@@@@@@@@@@@@@@@@@@@@\n");




		xSemaphoreTake(handFlexHandle, portMAX_DELAY);

		switch(movement_detect){
			case FIST:
				Fist(tx_buffer);
				break;

			case OKAY_SIGN:
				Okay_sign(tx_buffer);
				break;

			case PEACE_SIGN:
				Peace_sign(tx_buffer);
				break;

			case POINTING:
				Pointing(tx_buffer);
				break;

			case GOOD_SIGN:
				Good_sign(tx_buffer);
				break;
		}

		xSemaphoreTake(handReleaseHandle, portMAX_DELAY);
		Release(tx_buffer);


	}

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

void Set_Target(uint8_t *buffer, const uint8_t CHANNEL, uint8_t target_low, uint8_t target_high){
	buffer[0] = 0x84;
	buffer[1] = CHANNEL;
	buffer[2] = target_low;
	buffer[3] = target_high;
}

/*Storing the speed to 140us/ms and channel number to a buffer.*/

void Set_Speed(uint8_t *buffer, const uint8_t CHANNEL){
	buffer[0] = 0x87;
	buffer[1] = CHANNEL;
	buffer[2] =	0x0C;
	buffer[3] = 0x01;
}

void Fist(uint8_t *tx_buffer){
    Set_Target(tx_buffer, CHANNEL_0, TARGET_MIN_LOW, TARGET_MIN_HIGH);
  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
    Set_Target(tx_buffer, CHANNEL_1, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MIN_LOW, TARGET_MIN_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MIN_LOW, TARGET_MIN_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}

void Okay_sign(uint8_t *tx_buffer){
    Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}

void Peace_sign(uint8_t *tx_buffer){
    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}

void Pointing(uint8_t *tx_buffer){
    Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
  	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}

void Good_sign(uint8_t *tx_buffer){
    Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}
void Release(uint8_t *tx_buffer){
	Set_Target(tx_buffer, CHANNEL_0, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
    Set_Target(tx_buffer, CHANNEL_1, TARGET_MIN_LOW, TARGET_MIN_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_2, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
//	Set_Target(tx_buffer, CHANNEL_3, TARGET_MAX_LOW, TARGET_MAX_HIGH);
//	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
	Set_Target(tx_buffer, CHANNEL_4, TARGET_MAX_LOW, TARGET_MAX_HIGH);
	HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, 4, 100);
}


