/*
 * motor_driver.h
 *
 *  Created on: 8 Eyl 2023
 *      Author: ogulc
 */

#include "main.h"

#ifndef SRC_MOTOR_DRIVER_H_
#define SRC_MOTOR_DRIVER_H_

/*Macros*/

#define CHANNEL_0 0
#define CHANNEL_1 0x01
#define CHANNEL_2 0x02
#define CHANNEL_3 0x03
#define CHANNEL_4 0x04

#define TARGET_MAX_LOW	0x30
#define TARGET_MAX_HIGH 0X54
#define SET_TARGET  0x84
#define TARGET_MIN_LOW	0x60
#define TARGET_MIN_HIGH	0x08

#define fist 		0
#define okay_sign 	1
#define peace_sign	2
#define pointing	3
#define good_sign	4
//uint8_t tx_buffer[8];

/*Function prototypes*/

void Set_Target(uint8_t *buffer, const uint8_t CHANNEL, uint8_t target_low, uint8_t target_high);

void Set_Speed(uint8_t *buffer, const uint8_t CHANNEL);


#endif /* SRC_MOTOR_DRIVER_H_ */
