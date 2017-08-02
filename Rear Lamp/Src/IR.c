/*
 * IR.c
 *
 *  Created on: Jul 17, 2017
 *      Author: F27285C
 */
#include "IR.h"
#include "signals.h"
int noOfOnes;
IRMessage IR_tToReturn;

IRMessage IRdecode(uint16_t message) {
	noOfOnes = 0;
	IR_tToReturn = failed;
	for(int i = 0; i < 16; i++) {
		if((1 << i) & message ) {
			noOfOnes++;
		}
	}
	switch(noOfOnes) {
	case 0: IR_tToReturn = idle; //in case we do not receive anything
			break;
	case 4: IR_tToReturn = obstacleOnTheRoad;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 8: IR_tToReturn = cryticalBrake;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 12: IR_tToReturn = goingToLeaveTheRoad;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 16: IR_tToReturn = goingToStop;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			break;

	default:IR_tToReturn = failed;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			break;
	}

	return IR_tToReturn;
}

int getDutyCycle(int msg) {
	int toReturn = -1;

	switch(msg) {
	case IR_IDLE: toReturn = 0;
				break;
	case IR_OBSTACLE: toReturn = IRPeriod / 4;
							break;
	case IR_BRAKE: toReturn = IRPeriod / 2;
						break;
	case IR_LEAVING: toReturn = IRPeriod / 4 + IRPeriod / 2;
							break;
	case IR_STOP: toReturn = IRPeriod ;
					break;
	default: break;
	}
	return toReturn;
}
