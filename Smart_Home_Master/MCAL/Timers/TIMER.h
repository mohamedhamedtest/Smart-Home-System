/*
 * TIMER.h
 *
 *  Created on: Aug 27, 2023
 *      Author: user
 */

#ifndef TIMER_H_
#define TIMER_H_

//configurations
//TIMER0
#define TCCR0_WGM00      6 //waveform generation mode bit0
#define TCCR0_WGM01      3 //waveform generation mode bit1
#define TCCR0_CS02       2 //prescaler bit 2
#define TCCR0_CS01       1 //prescaler bit 1
#define TCCR0_CS00       0 //prescaler bit 0
#define TCCR0_COM01      5
#define TCCR0_COM00      4

//TIMER1
//TCCR1A
#define TCCR1A_COM1A0    6
#define TCCR1A_COM1A1    7
#define TCCR1A_COM1B0    4
#define TCCR1A_COM1B1    5
#define TCCR1A_WGM10     0
#define TCCR1A_WGM11     1
//TCCR1B
#define TCCR1B_WGM12     3
#define TCCR1B_WGM13     4
#define TCCR1B_CS10      0
#define TCCR1B_CS11      1
#define TCCR1B_CS12      2
#define PRESCALLER_FREQ  0b11111000
#define Divide_by_8      2
#define Divide_by_64     3
#define Divide_by_256    4




#define TIMSK_OCIE0      1
#define TIMSK_TOIE0      0

#define OK               1
#define NOT_OK           0
#define NULL     ((void*)0)

//prototypes
//timer0
void TIMER0_Init(void);
void TIMER0_STOP(void);
u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

//timer1
void TIMER1_Init(void);
void TIMER1_voidSetChannelAtCompMatch(u16 Copy_u16CompareMatch);
void TIMER1_voidSetChanne2AtCompMatch(u16 Copy_u16CompareMatch);
void TIMER1_voidSetISR(u16 Copy_u16Top);
#endif /* TIMER_H_ */
