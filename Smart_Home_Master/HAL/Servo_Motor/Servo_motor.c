/*
 * Servo_motor.c
 *
 *  Created on: Sep 10, 2023
 *      Author: user
 */

#include "Servo_motor.h"
#include <avr/io.h>


void SERVO_INIT(void)
{
	//set PORTD pin 5, 4 as output
	DIO_SetPinDirection(DIO_PORTD , DIO_PIN5, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD , DIO_PIN4, DIO_PIN_OUTPUT);
	//Timer1 as Fast PWM, TOP in ICR1, Clear OC1A on compare match, prescalar -> 8
	TIMER1_Init();
	TIMER1_voidSetISR(19999);
	TCNT1=0;
	SERVO_CLOSE_DOOR();
	SERVO_CLOSE_GARAGE();

}

void SERVO_OPEN_DOOR(void)
{
	//2ms -> +90 degree
	//tick time = 8/8MHZ = 1x10^6
	//2ms/1us = 2000
	TIMER1_voidSetChannelAtCompMatch(2000);
}

void SERVO_CLOSE_DOOR(void)
{
	//1.5ms -> 0 degree
	//tick time = 8/8MHZ = 1x10^6
	//1.5ms/1us = 2000
	TIMER1_voidSetChannelAtCompMatch(1500);
}

void SERVO_OPEN_GARAGE(void)
{
	//2ms -> +90 degree
	//tick time = 8/8MHZ = 1x10^6
	//2ms/1us = 2000
	TIMER1_voidSetChanne2AtCompMatch(2000);
}

void SERVO_CLOSE_GARAGE(void)
{
	//2ms -> +90 degree
	//tick time = 8/8MHZ = 1x10^6
	//2ms/1us = 1500
	TIMER1_voidSetChanne2AtCompMatch(1500);
}


u8 DOOR_STATUS(void)
{
	if(OCR1A == 2000)
	{
		return DOOR_OPEN;
	}
	else if(OCR1B == 1500)
	{
		return DOOR_CLOSED;
	}
}
u8 GARAGE_STATUS(void)
{
	if(OCR1B == 2000)
	{
		return GARAGE_OPEN;
	}
	else if(OCR1B == 1500)
	{
		return GARAGE_CLOSED;
	}
}
