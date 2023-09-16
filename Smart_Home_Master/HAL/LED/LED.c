/*
 * LED.c
 *
 *  Created on: Sep 10, 2023
 *      Author: user
 */
#include"LED.h"
#include<avr/io.h>

void LED_voidInit(u8 PortName, u8 PinNumber)
{
	//set wanted pin as output
	DIO_SetPinDirection(PortName, PinNumber, DIO_PIN_OUTPUT);
}

void LED_voidTurnON(u8 PortName, u8 PinNumber)
{
	//set wanted pin to one (ON)
	DIO_SetPinValue(PortName, PinNumber, DIO_HIGH);
}

void LED_voidTurnOFF(u8 PortName, u8 PinNumber)
{
	//set wanted pin to one (OFF)
	DIO_SetPinValue(PortName, PinNumber, DIO_LOW);
}

u8 LED_u8CheckStatus(u8 PortName, u8 PinNumber)
{
	return DIO_GetPinValue(PortName,PinNumber);
}

