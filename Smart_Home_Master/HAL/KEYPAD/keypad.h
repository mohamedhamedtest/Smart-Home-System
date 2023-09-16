/*
 * keypad.h
 *
 *  Created on: Aug 21, 2023
 *      Author: user
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include"../../MCAL/DIO/DIO.h"


//configurations
//ROWS
#define KPD_R0_PORT DIO_PORTA
#define KPD_R0_PIN  DIO_PIN0

#define KPD_R1_PORT DIO_PORTA
#define KPD_R1_PIN  DIO_PIN1

#define KPD_R2_PORT DIO_PORTA
#define KPD_R2_PIN  DIO_PIN2

#define KPD_R3_PORT DIO_PORTA
#define KPD_R3_PIN  DIO_PIN3

//COLUMNS
#define KPD_C0_PORT DIO_PORTA
#define KPD_C0_PIN  DIO_PIN4

#define KPD_C1_PORT DIO_PORTA
#define KPD_C1_PIN  DIO_PIN5

#define KPD_C2_PORT DIO_PORTA
#define KPD_C2_PIN  DIO_PIN6

#define KPD_C3_PORT DIO_PORTA
#define KPD_C3_PIN  DIO_PIN7

#define KPD_PRESSED_KEY DIO_PORT_INPUT
#define KPD_NOT_PRESSED DIO_PORT_OUTPUT

//to avoid magic numbers
#define ROW_NUMBER 4
#define COL_NUMBER 4

#define KPD_VALUES {{'7', '8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}}

//prototypes
void KPD_INIT(void);
char KPD_GETKEY(void);
u8 Get_Number(u8 num);


#endif /* KEYPAD_H_ */
