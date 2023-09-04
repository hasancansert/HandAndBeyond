/*
 * MotorDriver.h
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */

#ifndef SRC_MOTORDRIVER_MOTORDRIVER_H_
#define SRC_MOTORDRIVER_MOTORDRIVER_H_

#include "FreeRTOS.h"
#include "task.h"




void MotorTaskFunction(void const * argument);
void MotorTaskInit(void);

#endif /* SRC_MOTORDRIVER_MOTORDRIVER_H_ */
