/*
 * IR.h
 *
 *  Created on: Jul 17, 2017
 *      Author: F27285C
 */

#ifndef IR_H_
#define IR_H_

#define IRPeriod 10000

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef enum IRMsg {idle,
				obstacleOnTheRoad,
				cryticalBrake,
				goingToLeaveTheRoad,
				goingToStop,
				failed} IRMessage;



IRMessage IRdecode(uint16_t message);
int getDutyCycle(int msg);





#endif /* IR_H_ */
