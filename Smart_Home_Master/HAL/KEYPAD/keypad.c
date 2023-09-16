/*
 * keypad.c
 *
 *  Created on: Aug 21, 2023
 *      Author: user
 */
#include"keypad.h"
#include<util/delay.h>
#include<avr/io.h>
#include"../../libs/STD_TYPES.h"
#include"../../libs/util.h"
#include"../../MCAL/DIO/DIO.h"

void KPD_INIT(void)
{
	//step1: configure row directions -> internal pullup -> input, value-> high
	DIO_SetPinDirection(KPD_R0_PORT, KPD_R0_PIN, DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_R1_PORT, KPD_R1_PIN, DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_R2_PORT, KPD_R2_PIN, DIO_PIN_INPUT);
	DIO_SetPinDirection(KPD_R3_PORT, KPD_R3_PIN, DIO_PIN_INPUT);

	DIO_SetPinValue(KPD_R0_PORT,KPD_R0_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_R1_PORT, KPD_R1_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_R2_PORT, KPD_R2_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_R3_PORT, KPD_R3_PIN, DIO_HIGH);

	//Step2: configure col directions ->output , value-> high
	DIO_SetPinDirection(KPD_C0_PORT, KPD_C0_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_C1_PORT, KPD_C1_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_C2_PORT, KPD_C2_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(KPD_C3_PORT, KPD_C3_PIN, DIO_PIN_OUTPUT);

	DIO_SetPinValue(KPD_C0_PORT,KPD_C0_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_C1_PORT, KPD_C1_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_C2_PORT, KPD_C2_PIN, DIO_HIGH);
	DIO_SetPinValue(KPD_C3_PORT, KPD_C3_PIN, DIO_HIGH);
}
char KPD_GETKEY(void)
{
	char u8RowLocal=0, u8ColLocal=0;
	char u8PinValueLocal=0;
	char KPD_u8RowPortArr[ROW_NUMBER] ={KPD_R0_PORT, KPD_R1_PORT,KPD_R2_PORT,KPD_R3_PORT };
	char KPD_u8RowPinArr[ROW_NUMBER] ={KPD_R0_PIN, KPD_R1_PIN,KPD_R2_PIN,KPD_R3_PIN };

	char KPD_u8ColPortArr[COL_NUMBER] ={KPD_C0_PORT, KPD_C1_PORT,KPD_C2_PORT,KPD_C3_PORT };
	char KPD_u8ColPinArr[COL_NUMBER] ={KPD_C0_PIN, KPD_C1_PIN,KPD_C2_PIN,KPD_C3_PIN};

	char KDP_u8values[ROW_NUMBER][COL_NUMBER] = KPD_VALUES;

	for(u8ColLocal=0 ;u8ColLocal < COL_NUMBER; u8ColLocal++)
	{
		DIO_SetPinValue(KPD_u8ColPortArr[u8ColLocal],KPD_u8ColPinArr[u8ColLocal], DIO_LOW);

		for(u8RowLocal=0;u8RowLocal < ROW_NUMBER; u8RowLocal++ )
		{
			u8PinValueLocal= DIO_GetPinValue(KPD_u8RowPortArr[u8RowLocal], KPD_u8RowPinArr[u8RowLocal]);
			if(u8PinValueLocal == KPD_PRESSED_KEY)
			{
				_delay_ms(50);
				u8PinValueLocal= DIO_GetPinValue(KPD_u8RowPortArr[u8RowLocal], KPD_u8RowPinArr[u8RowLocal]);
				while(u8PinValueLocal == KPD_PRESSED_KEY)
				{
					u8PinValueLocal= DIO_GetPinValue(KPD_u8RowPortArr[u8RowLocal], KPD_u8RowPinArr[u8RowLocal]);

				}
				return KDP_u8values[u8RowLocal][u8ColLocal];
			}
		}
		DIO_SetPinValue(KPD_u8ColPortArr[u8ColLocal], KPD_u8ColPinArr[u8ColLocal], DIO_HIGH);
	}
	return KPD_NOT_PRESSED;
}

u8 Get_Number(u8 num) //to convert characters to integer numbers
{
	switch(num)
	{
	case '0': return 0; break;
	case '1': return 1; break;
	case '2': return 2; break;
	case '3': return 3; break;
	case '4': return 4; break;
	case '5': return 5; break;
	case '6': return 6; break;
	case '7': return 7; break;
	case '8': return 8; break;
	case '9': return 9; break;
	default: break;
	}
	return 0;
}
