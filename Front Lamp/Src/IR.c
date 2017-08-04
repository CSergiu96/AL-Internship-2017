/*
 * IR.c
 *
 *  Created on: Jul 17, 2017
 *      Author: F27285C
 */
#include "IR.h"
int noOfOnes;
IRMessage IR_tReceivedFirstMessage;
IRMessage IR_tReceivedSecondMessage;
IRMessage IR_tReceivedThirdMessage;
uint16_t IR_ui16message = 0;

IRMessage IR_tReceivedMessage;
IRMessage toReturn;
int IR_intcounter;

/**
* @brief This function reads the message from the transmitter
* @description reads 16 values of zeros and ones and put them together as a message
*/
void readIRMessage() {
	if(IR_intcounter % 16 == 0 && IR_intcounter < 20) {
		 IR_tReceivedFirstMessage = IRdecode(IR_ui16message);
	 }
	 if(IR_intcounter % 32 == 0 && IR_intcounter < 40) {
		 IR_tReceivedSecondMessage = IRdecode(IR_ui16message);
	 }
	 if(IR_intcounter % 48 == 0) {
		 IR_tReceivedThirdMessage = IRdecode(IR_ui16message);
		 if(IR_tReceivedFirstMessage == IR_tReceivedSecondMessage && IR_tReceivedFirstMessage == IR_tReceivedThirdMessage) {
			 IR_tReceivedMessage = IR_tReceivedFirstMessage;
		 } else if(IR_tReceivedSecondMessage == IR_tReceivedThirdMessage) {
			 IR_tReceivedMessage = IR_tReceivedSecondMessage;
		 } else {
			 IR_tReceivedMessage = IR_tReceivedThirdMessage;
		 }

	 }
}

/**
* @brief This function decodify the IR message
* @description takes as a parameter a 16 bits data and in function of how many bits are setted returns a certain message
*/
IRMessage IRdecode(uint16_t IR_ui16message) {
	noOfOnes = 0;
	toReturn = failed;
	for(int i = 0; i < 16; i++) {
		if((1 << i) & IR_ui16message ) {
			noOfOnes++;
		}
	}
	switch(noOfOnes) {
	case 0: toReturn = idle; //in case we do not recive anything
			break;

	case 4:toReturn = obstacleOnTheRoad;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 8: toReturn = cryticalBrake;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 12: toReturn = goingToLeaveTheRoad;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;

	case 16: toReturn = goingToStop;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			break;

	default:toReturn = failed;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			break;
	}

	return toReturn;
}

/**
* @brief This function return the duty cycle in order to transmit a certain message based on PWM
* @description takes as a parameter an IRMessage type and in function of this it will return the duty cycle for the PWM generation in order to transmit
* 			   that message
*/
int getDutyCycle(IRMessage IR_tmsg) {
	int toReturn = -1;

	switch(IR_tmsg) {
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
