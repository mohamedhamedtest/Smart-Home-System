/*
b * ADC.h
 *
 *  Created on: Aug 24, 2023
 *      Author: user
 */

#ifndef ADC_H_
#define ADC_H_


//configuration
#define ADC_PORT  DIO_PORTA

#define ADC0_PIN  DIO_PIN0
#define ADC1_PIN  DIO_PIN1
#define ADC2_PIN  DIO_PIN2
#define ADC3_PIN  DIO_PIN3
#define ADC4_PIN  DIO_PIN4
#define ADC5_PIN  DIO_PIN5
#define ADC6_PIN  DIO_PIN6
#define ADC7_PIN  DIO_PIN7

//ADMUX: ADC Multiplexer selection
#define ADMUX_REFS1    7
#define ADMUX_REFS0    6
#define ADMUX_ADLAR    5
#define ADMUX_MUX4     4
#define ADMUX_MUX3     3
#define ADMUX_MUX2     2
#define ADMUX_MUX1     1
#define ADMUX_MUX0     0

//ADCSRA: ADC control and status register
#define ADCSRA_ADEN    7 //ADC enable
#define ADCSRA_ADSC    6 //start conversion
#define ADCSRA_ADATE   5 //auto trigger enable
#define ADCSRA_ADIF    4 //interrupt flag
#define ADCSRA_ADIE    3 //interrupt enable
#define ADCSRA_ADPS2   2 //prescaler bit2
#define ADCSRA_ADPS1   1 //prescaler bit1
#define ADCSRA_ADPS0   0 //prescaler bit0

//prototypes
void ADC_voidInit(void);
u8 ADC_u8GetChannelReading(void);



#endif /* ADC_H_ */
