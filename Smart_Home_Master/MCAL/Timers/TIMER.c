/*
 * TIMER.c
 *
 *  Created on: Aug 27, 2023
 *      Author: user
 */

#include"../../libs/STD_TYPES.h"
#include"../../MCAL/DIO/DIO.h"
#include"../../libs/util.h"
#include"TIMER.h"
#include<avr/io.h>
#include <avr/interrupt.h>

//timer0
void (*TIMER0_pvCallBackFunc)(void) = NULL;

void TIMER0_Init(void)
{
	//Config OCR0
	//OCR0 = the value to compare with
	OCR0 = 78; //to achieve tick equal to 10 msec

	//Set timer mode
	//Set the mode as Compare match
	Set_Bit(TCCR0, TCCR0_WGM01);
	Clear_Bit(TCCR0, TCCR0_WGM00);

	//Configure clock
	//set as clk/1024
	Set_Bit(TCCR0, TCCR0_CS00);
	Clear_Bit(TCCR0, TCCR0_CS01);
	Set_Bit(TCCR0, TCCR0_CS02);

	//Enable timer 0 interrupt for compare match
	Set_Bit(TIMSK, TIMSK_OCIE0);

}

void TIMER0_STOP(void)
{
	//disable the clock to stop the counter
	Clear_Bit(TCCR0, TCCR0_CS00);
	Clear_Bit(TCCR0, TCCR0_CS01);
	Clear_Bit(TCCR0, TCCR0_CS02);
}

u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 u8ErrorState_Local = OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		u8ErrorState_Local = NOT_OK;
	}
	return u8ErrorState_Local;
}


//timer1
void TIMER1_Init(void)
{
	//Clear OC1A on compare match
	Set_Bit(TCCR1A, TCCR1A_COM1A1);
	Clear_Bit(TCCR1A, TCCR1A_COM1A0);
	//Clear OC1B on compare match
	Set_Bit(TCCR1A, TCCR1A_COM1B1);
	Clear_Bit(TCCR1A, TCCR1A_COM1B0);
	//Fast PWM, TOP in ICR1
	Set_Bit(TCCR1A, TCCR1A_WGM11);
	Clear_Bit(TCCR1A, TCCR1A_WGM10);
	Set_Bit(TCCR1B, TCCR1B_WGM12);
	Set_Bit(TCCR1B, TCCR1B_WGM13);
	//prescalar -> 8
	TCCR1B &= PRESCALLER_FREQ;
	TCCR1B |= Divide_by_8;

}

void TIMER1_voidSetChannelAtCompMatch(u16 Copy_u16CompareMatch)
{
	OCR1A = Copy_u16CompareMatch;
}

void TIMER1_voidSetChanne2AtCompMatch(u16 Copy_u16CompareMatch)
{
	OCR1B = Copy_u16CompareMatch;
}


void TIMER1_voidSetISR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}









//overflow
/*void __vector_11(void) __attribute((signal));
void __vector_11(void)
{

	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}*/
