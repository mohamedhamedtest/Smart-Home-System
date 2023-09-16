/*
 * LCD.c
 *
 *  Created on: Aug 20, 2023
 *      Author: user
 */
#include "LCD.h"

void LCD_KICK(void){
	LCD_CONTROL &= ~(1<<EN_SWITCH);
	_delay_ms(50);
	LCD_CONTROL |= (1<<EN_SWITCH);

}

void LCD_IS_BUSY_CHECK(void){
	DATA_DIR_LCD_PORT = 0x00;
	LCD_CONTROL |= (1<< RW);
	LCD_CONTROL &= ~(1<< RS_SWITCH);

	LCD_KICK();

	DATA_DIR_LCD_PORT = 0xFF;
	LCD_CONTROL &= ~(1<<RW);
}

void LCD_INIT(void){
	_delay_ms(20);
	DATA_DIR_LCD_CONTROL |= (1<<EN_SWITCH | 1<<RW | 1<<RS_SWITCH);
	LCD_CONTROL &= ~(1<<EN_SWITCH | 1<<RW | 1<<RS_SWITCH);

	DATA_DIR_LCD_PORT = 0xFF;
	_delay_ms(15);

	LCD_CLEAR_ALL_SCREEN();

#ifdef EIGHT_BIT_MODE
	LCD_SEND_A_COMMAND(LCD_FUNCTION_8BIT_2LINES);
#endif

#ifdef FOUR_BIT_MODE
	LCD_SEND_A_COMMAND(0x02);
	LCD_SEND_A_COMMAND(LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_SEND_A_COMMAND(LCD_ENTRY_MODE);
	LCD_SEND_A_COMMAND(LCD_BEGIN_AT_FIRST_RAW);
	LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR_OFF);


}

void LCD_CLEAR_ALL_SCREEN(void){
	LCD_SEND_A_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if(line == 0)
	{
		if(position < 16 && position >= 0)
		{
			LCD_SEND_A_COMMAND(0x80 + position);
		}
	}
	else if(line == 1)
	{
		if(position < 16 && position >= 0)
		{
			LCD_SEND_A_COMMAND(0xC0 + position);
		}
	}
}

void LCD_SEND_A_COMMAND(unsigned char command)
{
#ifdef EIGHT_BIT_MODE
	LCD_IS_BUSY_CHECK();
	LCD_PORT = command;
	LCD_CONTROL &= ~(1<<RW | 1<<RS_SWITCH);

	LCD_KICK();
#endif

#ifdef FOUR_BIT_MODE
	LCD_IS_BUSY_CHECK();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CONTROL &= ~(1<<RW | 1<<RS_SWITCH);
	LCD_KICK();

	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CONTROL &= ~(1<<RW | 1<<RS_SWITCH);
	LCD_KICK();
#endif

}

void SEND_A_CHAR(unsigned char character)
{
#ifdef EIGHT_BIT_MODE
	LCD_IS_BUSY_CHECK();
	LCD_PORT = ((character) << DATA_SHIFT);
	LCD_CONTROL &= ~(1<<RW);
	LCD_CONTROL |= (1<<RS_SWITCH);

	LCD_KICK();
#endif

#ifdef FOUR_BIT_MODE
	LCD_IS_BUSY_CHECK();
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CONTROL &= ~(1<<RW);
	LCD_CONTROL |= (1<<RS_SWITCH);
	LCD_KICK();

	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CONTROL &= ~(1<<RW);
	LCD_CONTROL |= (1<<RS_SWITCH);
	LCD_KICK();
#endif
}

void SEND_A_STRING(char* string)
{	int count=0;
	while(*string > 0)
	{
		count++;
		SEND_A_CHAR(*string++);
		if(count == 16)
		{
			LCD_GOTO_XY(1, 0);
		}
		else if(count == 32)
		{
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			count=0;
		}
	}
}

void LCD_DISPLAY_NUM(int num)
{
	char str[7];
	sprintf(str,"%d", num);
	SEND_A_STRING(str);
}

void LCD_DISPLAY_REAL_NUM(double num)
{
	char str[16];

	char* tmpsign = (num < 0) ? "-" : "";
	float tmpval = (num < 0 ) ? -num:num; //625.132

	int tmpint1 = tmpval; //625
	float tmpfrac = tmpval - tmpint1; //.132
	int tmpint2 = tmpfrac*10000; //1320

	sprintf(str, "%s%d.%04d",tmpsign,tmpint1,tmpint2);
	SEND_A_STRING(str);

}
