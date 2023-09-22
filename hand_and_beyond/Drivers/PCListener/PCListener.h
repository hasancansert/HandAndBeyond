/*
 * PCListener.h
 *
 *  Created on: Sep 21, 2023
 *      Author: baris
 */

#ifndef PCLISTENER_PCLISTENER_H_
#define PCLISTENER_PCLISTENER_H_

#define MESSAGE_SIZE 4

#define COMMAND_SET_MOTOR_POSITION 		0x01
#define COMMAND_SET_MOTOR_SPEED 		0x02
#define COMMAND_SET_MOTOR_ACCELERATION 	0x03
#define COMMAND_HAND_POSITION_POINTING 	0x10
#define COMMAND_HAND_POSITION_FIST 		0x11
#define COMMAND_HAND_POSITION_ROCK 		0x12
#define COMMAND_HAND_POSITION_FUCK 		0x13
#define COMMAND_HAND_POSITION_THUMB		0x14
#define COMMAND_HAND_POSITION_OPEN		0x15



//static uint8_t buffer[COMMAND_SIZE];


void UI_Init(void);
void UARTReceiveTaskInit(void);
void UARTReceiveTask(void const *argument);


#endif /* PCLISTENER_PCLISTENER_H_ */