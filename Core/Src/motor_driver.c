/*
 * motor_driver.c
 *
 *  Created on: 8 Eyl 2023
 *      Author: ogulc
 */

#include "motor_driver.h"

/*Storing the channel number and target position to a buffer.*/

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


