/*
 * LED.h
 *
 *  Created on: Sep 10, 2023
 *      Author: user
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

//includes
#include "../../libs/STD_TYPES.h"
#include "../../libs/util.h"
#include "../../MCAL/DIO/DIO.h"

//prototypes
void LED_voidInit(u8 PortName, u8 PinNumber);
void LED_voidTurnON(u8 PortName, u8 PinNumber);
void LED_voidTurnOFF(u8 PortName, u8 PinNumber);
u8 LED_u8CheckStatus(u8 PortName, u8 PinNumber);



#endif /* HAL_LED_LED_H_ */
