/*
 * PCListener.c
 *
 *  Created on: Sep 21, 2023
 *      Author: baris
 */
#include <MotorDriver.h>
#include <PCListener.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

uint8_t rx_buffer_size = 4;
uint8_t buffer[MESSAGE_SIZE];
uint8_t rx_index = 0;

void UI_Init(void){

	HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_UART_Receive_IT(&huart2, buffer, MESSAGE_SIZE);
}

void UARTReceiveTask(void const *argument){

	uint8_t message[4];
    uint8_t command;
    uint8_t motor_id;
    uint16_t value;

	for(;;)
	{
		if (xQueueReceive(xQueue, &message, portMAX_DELAY))
	    {
	    	command = message[0];
	    	motor_id = message[1];
	    	value = ( ( (uint16_t) message[2] ) << 8) | (uint16_t) message[3];

	        switch(command) {
	            case COMMAND_SET_MOTOR_POSITION:
	                set_motor_position(motor_id, value);
	                break;

	            case COMMAND_SET_MOTOR_SPEED:
	                set_motor_speed(motor_id, value);
	                break;

	            case COMMAND_SET_MOTOR_ACCELERATION:
	                set_motor_acceleration(motor_id, value);
	                break;

	            case COMMAND_HAND_POSITION_POINTING:
	    		   set_hand_position(POINTING);
	    		   break;
	    	   case COMMAND_HAND_POSITION_FIST:
	    		   set_hand_position(FIST);
	    		   break;

	    	   case COMMAND_HAND_POSITION_ROCK:
	    		   set_hand_position(ROCK);
	    		   break;

	    	   case COMMAND_HAND_POSITION_FUCK:
	    		   set_hand_position(FUCK);
	    		   break;

	    	   case COMMAND_HAND_POSITION_THUMB:
	    		   set_hand_position(THUMB);
	    		   break;

	    	   case COMMAND_HAND_POSITION_OPEN:
	    		   set_hand_position(OPEN);
	    		   break;

	            default:
	                // Unknown command
	                break;
	        }
	    }
	  }
}

void UARTReceiveTaskInit(void){

	TaskFunction_t UARTTask = UARTReceiveTask;

	xTaskCreate(UARTTask,
				"UART Task",
				128,
				NULL,//(void *) &hadc1
				tskIDLE_PRIORITY + 1,
				NULL );
}

void USART2_IRQHandler(void)
{

  /* USER CODE BEGIN USART2_IRQn 0 */

	if (USART2->SR & USART_SR_RXNE)  // Check if data is available to read
	    {
			buffer[rx_index++] = (uint8_t)(USART2->DR);  // Read data

	        if (rx_index >= MESSAGE_SIZE)  // If 10 bytes have been read, reset the index or do other processing
	        {
	        	rx_index = 0;
	        	xQueueSendFromISR(xQueue, buffer, pdFALSE);
	        	HAL_UART_IRQHandler(&huart2);
	        }
	    }

  /* USER CODE END USART2_IRQn 0 */

  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}








