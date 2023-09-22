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

#define FINGER_CLOSE_POSITION 1500
#define FINGER_OPEN_POSITION 250

#define THUMB_FINGER 	0x00
#define LITTLE_FINGER 	0x01
#define RING_FINGER 	0x02
#define MIDDLE_FINGER 	0x03
#define INDEX_FINGER 	0x04
#define WRIST			0x05

#define SET_TARGET  		0x84
#define SET_SPEED 			0x87
#define SET_ACCELERATION	0x89

#define POINTING 	0x10
#define FIST		0x11
#define	ROCK		0x12
#define FUCK		0x13
#define THUMB		0x14
#define OPEN		0x15




void set_motor_position(uint8_t channel, uint16_t position);
void set_motor_speed(uint8_t channel, uint32_t speed);
void set_all_motor_speed(uint32_t speed);
void set_motor_acceleration(uint8_t channel, uint32_t acceleration);
void set_all_motor_acceleration(uint32_t acceleration);
void set_hand_position(const uint32_t position);


void MotorTaskFunction(void const * argument);
void MotorTaskInit(void);

#endif /* SRC_MOTORDRIVER_MOTORDRIVER_H_ */
