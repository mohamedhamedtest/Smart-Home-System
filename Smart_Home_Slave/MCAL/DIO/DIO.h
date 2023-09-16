/*
 * DIO.h
 *
 *  Created on: Aug 17, 2023
 *      Author: user
 */

#ifndef DIO_H_
#define DIO_H_

#include "../../libs/STD_TYPES.h"
//port definition
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

//pin definition
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

//pin directions
#define DIO_PIN_INPUT  0
#define DIO_PIN_OUTPUT 1

//pin value
#define DIO_HIGH 1
#define DIO_LOW  0

//port value
#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_INPUT 0

//prototypes of functions IO pins
//set port direction
void DIO_SetPortDirection(u8 u8PortIdCopy,u8 u8PortDirCopy );
//set pin direction
void DIO_SetPinDirection(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8PinDirCopy );
//set port value
void DIO_SetPortValue(u8 u8PortIdCopy,u8 u8PortValCopy);
//set pin value
void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8PinValCopy);
//get pin value
u8 DIO_GetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy);

#endif /* DIO_H_ */
