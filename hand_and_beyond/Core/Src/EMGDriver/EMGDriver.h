/*
 * EMGDriver.h
 *
 *  Created on: Sep 4, 2023
 *      Author: baris
 */

#ifndef SRC_EMGDRIVER_EMGDRIVER_H_
#define SRC_EMGDRIVER_EMGDRIVER_H_

#include "FreeRTOS.h"
#include "task.h"


void EmgTaskFunction(void const * argument);
void EmgTaskInit(void);

#endif /* SRC_EMGDRIVER_EMGDRIVER_H_ */
