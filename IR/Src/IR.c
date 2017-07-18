/*
 * IR.c
 *
 *  Created on: Jul 17, 2017
 *      Author: F27285C
 */
#include "IR.h"
int noOfOnes;
IRMessage toReturn;

IRMessage decode(uint16_t message) {
	noOfOnes = 0;
	toReturn = failed;
	for(int i = 0; i < 16; i++) {
		if((1 << i) & message ) {
			noOfOnes++;
		}
	}
	switch(noOfOnes) {
	case 0: toReturn = idle; //in case we do not recive anything
			break;
	case 3:
	case 4:
	case 5: toReturn = obstacleOnTheRoad;HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
	case 7:
	case 8:
	case 9: toReturn = cryticalBrake;HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
	case 11:
	case 12:
	case 13: toReturn = goingToLeaveTheRoad;HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
	case 15:
	case 16: toReturn = goingToStop;HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			break;
	default:toReturn = failed;HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			break;
	}

	return toReturn;
}

int code(IRMessage msg) {
	int toReturn = -1;

	switch(msg) {
	case idle: toReturn = 0;
				break;
	case obstacleOnTheRoad: toReturn = IRPeriod / 4;
							break;
	case cryticalBrake: toReturn = IRPeriod / 2;
						break;
	case goingToLeaveTheRoad: toReturn = IRPeriod / 4 + IRPeriod / 2;
							break;
	case goingToStop: toReturn = IRPeriod ;
					break;
	default: break;
	}
	return toReturn;
}
