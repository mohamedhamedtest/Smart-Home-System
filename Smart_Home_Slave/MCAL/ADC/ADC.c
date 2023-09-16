/*
 * ADC.c
 *
 *  Created on: Aug 24, 2023
 *      Author: user
 */

#include "../../libs/STD_TYPES.h"
#include "../../libs/util.h"
#include<avr/io.h>
#include"ADC.h"


void ADC_voidInit(void)
{
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
	Set_Bit(ADMUX, ADMUX_REFS0);
	Set_Bit(ADMUX, ADMUX_REFS1);

	//activate right adjusted
	Clear_Bit(ADMUX, ADMUX_ADLAR);

	//set prescaler to divide by 64
	Set_Bit(ADCSRA, ADCSRA_ADPS2);
	Set_Bit(ADCSRA, ADCSRA_ADPS1);
	Clear_Bit(ADCSRA, ADCSRA_ADPS0);

	//enable peripheral
	Set_Bit(ADCSRA, ADCSRA_ADEN);
}

u8 ADC_u8GetChannelReading(void)
{
	u16 Local_u8ReadValue;
	//start conversion
	Set_Bit(ADCSRA, ADCSRA_ADSC);
	//polling
	while((Read_Bit(ADCSRA, ADCSRA_ADIF)) == 0);
	//read ADC from the two register
	Local_u8ReadValue |= ADCL;
	Local_u8ReadValue |= (ADCH << 8);
	return Local_u8ReadValue;
}
