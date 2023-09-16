/*
 * LCD.h
 *
 *  Created on: Aug 20, 2023
 *      Author: user
 */

#ifndef LCD_DRIVER_LCD_H_
#define LCD_DRIVER_LCD_H_

#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#include<stdlib.h>
#include<stdio.h>

#define LCD_PORT PORTC
#define DATA_DIR_LCD_PORT DDRC
#define DATA_SHIFT 0

#define LCD_CONTROL PORTD
#define DATA_DIR_LCD_CONTROL DDRD
#define RS_SWITCH 1
#define RW 2
#define EN_SWITCH 3

//8_bit or 4_bit mode
#define EIGHT_BIT_MODE
//#define FOUR_BIT_MODE

#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR				    		(0x0E)
#define LCD_DISP_ON_CURSOR_OFF  					(0x0C)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


void LCD_IS_BUSY_CHECK(void);
void LCD_KICK(void);
void LCD_SEND_A_COMMAND(unsigned char command);
void SEND_A_CHAR(unsigned char character);
void SEND_A_STRING(char* string);
void LCD_INIT(void);
void LCD_CLEAR_ALL_SCREEN(void);
void LCD_GOTO_XY(unsigned char line, unsigned char position);
void LCD_DISPLAY_NUM(int num);
void LCD_DISPLAY_REAL_NUM(double num);

#endif /* LCD_DRIVER_LCD_H_ */
