/*
 * DIO.c
 *
 *  Created on: Aug 17, 2023
 *      Author: user
 */


#include<util/delay.h>
#include<avr/io.h>
#include "../../libs/STD_TYPES.h"
#include "../../libs/util.h"
#include"DIO.h"


//set port direction
void DIO_SetPortDirection(u8 u8PortIdCopy,u8 u8PortDirCopy)
{
	switch(u8PortIdCopy)
	{
	case DIO_PORTA: DDRA = u8PortDirCopy; break;
	case DIO_PORTB: DDRB = u8PortDirCopy; break;
	case DIO_PORTC: DDRC = u8PortDirCopy; break;
	case DIO_PORTD: DDRD = u8PortDirCopy; break;
	}
}

//set pin direction
void DIO_SetPinDirection(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8PinDirCopy )
{
	if((u8PortIdCopy <= DIO_PORTD)&&(u8PinIdCopy <= DIO_PIN7))
	{
		if(u8PinDirCopy==DIO_PIN_OUTPUT)
		{
			switch(u8PortIdCopy)
			{
			case DIO_PORTA: Set_Bit(DDRA, u8PinIdCopy); break;
			case DIO_PORTB: Set_Bit(DDRB, u8PinIdCopy); break;
			case DIO_PORTC: Set_Bit(DDRC, u8PinIdCopy); break;
			case DIO_PORTD: Set_Bit(DDRD, u8PinIdCopy); break;
			}
		}
		else if(u8PinDirCopy==DIO_PIN_INPUT)
		{
			switch(u8PortIdCopy)
			{
			case DIO_PORTA: Clear_Bit(DDRA, u8PinIdCopy); break;
			case DIO_PORTB: Clear_Bit(DDRB, u8PinIdCopy); break;
			case DIO_PORTC: Clear_Bit(DDRC, u8PinIdCopy); break;
			case DIO_PORTD: Clear_Bit(DDRD, u8PinIdCopy); break;
			}
		}
	}
}
//set port value
void DIO_SetPortValue(u8 u8PortIdCopy,u8 u8PortValCopy)
{
	switch(u8PortIdCopy)
	{
	case DIO_PORTA: PORTA = u8PortValCopy; break;
	case DIO_PORTB: PORTB = u8PortValCopy; break;
	case DIO_PORTC: PORTC = u8PortValCopy; break;
	case DIO_PORTD: PORTD = u8PortValCopy; break;
	}
}
//set pin value
void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy, u8 u8PinValCopy)
{
	if((u8PortIdCopy <= DIO_PORTD)&&(u8PinIdCopy <= DIO_PIN7))
		{
			if(u8PinValCopy == DIO_HIGH)
			{
				switch(u8PortIdCopy)
				{
				case DIO_PORTA: Set_Bit(PORTA, u8PinIdCopy); break;
				case DIO_PORTB: Set_Bit(PORTB, u8PinIdCopy); break;
				case DIO_PORTC: Set_Bit(PORTC, u8PinIdCopy); break;
				case DIO_PORTD: Set_Bit(PORTD, u8PinIdCopy); break;
				}
			}
			else if(u8PinValCopy == DIO_LOW)
			{
				switch(u8PortIdCopy)
				{
				case DIO_PORTA: Clear_Bit(PORTA, u8PinIdCopy); break;
				case DIO_PORTB: Clear_Bit(PORTB, u8PinIdCopy); break;
				case DIO_PORTC: Clear_Bit(PORTC, u8PinIdCopy); break;
				case DIO_PORTD: Clear_Bit(PORTD, u8PinIdCopy); break;
				}
			}

		}
}
//get pin value
u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
	u8 u8ResultLocal;
	if((u8PortIdCopy <= DIO_PORTD) && (u8PinIdCopy <= DIO_PIN7))
	{
		switch(u8PortIdCopy)
		{
		case DIO_PORTA: u8ResultLocal = Read_Bit(PINA, u8PinIdCopy); break;
		case DIO_PORTB: u8ResultLocal = Read_Bit(PINB, u8PinIdCopy); break;
		case DIO_PORTC: u8ResultLocal = Read_Bit(PINC, u8PinIdCopy); break;
		case DIO_PORTD: u8ResultLocal = Read_Bit(PIND, u8PinIdCopy); break;
		}

	}
	return u8ResultLocal;
}
