/*
 * task_init.h
 *
 *  Created on: 8 Eyl 2023
 *      Author: ogulc
 */


#ifndef SRC_TASK_INIT_H_
#define SRC_TASK_INIT_H_

extern UART_HandleTypeDef huart6;

void MotorControlTask(void *params);

void Task_Init(void);

void MotorControl_Task_Init(void);


#endif /* SRC_TASK_INIT_H_ */

