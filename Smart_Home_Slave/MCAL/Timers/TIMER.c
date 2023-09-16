/*
 * TIMER.c
 *
 *  Created on: Aug 27, 2023
 *      Author: user
 */


#include"TIMER.h"


//timer0
void (*TIMER0_pvCallBackFunc)(void) = NULL;

void TIMER0_Init(void)
{
	//Configuration OCR0
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

//CTC mode timer0 ISR
/*void __vector_10(void) __attribute((signal));
void __vector_10(void)
{

	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}*/
