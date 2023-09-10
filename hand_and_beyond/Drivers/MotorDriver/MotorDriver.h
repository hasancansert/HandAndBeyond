/*
 * MotorDriver.h
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */
#pragma once
#ifndef SRC_MOTORDRIVER_MOTORDRIVER_H_
#define SRC_MOTORDRIVER_MOTORDRIVER_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

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

#define FIST 		0
#define OKAY_SIGN 	1
#define PEACE_SIGN	2
#define POINTING	3
#define GOOD_SIGN	4

//uint8_t tx_buffer[8];



void Set_Target(uint8_t *buffer, const uint8_t CHANNEL, uint8_t target_low, uint8_t target_high);
void Set_Speed(uint8_t *buffer, const uint8_t CHANNEL);
void Fist(uint8_t *tx_buffer);
void Okay_sign(uint8_t *tx_buffer);
void Peace_sign(uint8_t *tx_buffer);
void Pointing(uint8_t *tx_buffer);
void Good_sign(uint8_t *tx_buffer);
void Release(uint8_t *tx_buffer);


void MotorTaskFunction(void const * argument);
void MotorTaskInit(void);

#endif /* SRC_MOTORDRIVER_MOTORDRIVER_H_ */
