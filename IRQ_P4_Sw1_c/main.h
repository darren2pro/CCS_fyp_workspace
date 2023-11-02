/*
 * main.h
 *
 *  Created on: Nov 2, 2023
 *      Author: User
 */

#include <msp430.h>

#ifndef MAIN_H_
#define MAIN_H_

void activateGPIO(void);
void clearP4_5_IFG(void);
void configureLED1(void);
void configureSwitch1(void);

#endif /* MAIN_H_ */
