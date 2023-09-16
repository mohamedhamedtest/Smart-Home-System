/*
 * EEPROM.c
 *
 *  Created on: Sep 9, 2023
 *      Author: user
 */

#include"EEPROM.h"
#include<avr/io.h>

void EEPROM_voidWriteByte( const u16 Copy_u16Address, const u8 Copy_u8Data)
{
	/* Wait for completion of previous write process*/
	while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
		;
	/* Set up address register */
	EEAR = Copy_u16Address;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EERE);
	if (EEDR != Copy_u8Data)//compare the value read to the value to be written
	{//if they are not equal then write the data
		EEDR = Copy_u8Data;//move the data to EEDR

		/* Write logical one to EEMWE */
		EECR |= (1 << EEMWE);
		/* Start EEPROM write by setting EEWE */
		EECR |= (1 << EEWE);
	}
	else
	{

	}

}

void EEPROM_voidWriteBlock( const u16 Copy_u16Address, const u8* P_u8DataArray,const u16 Copy_u16Size)
{

	u16 counter = 0;//Bytes write counter
	while (counter < Copy_u16Size)
	{
		/* Wait for completion of previous write process*/
		while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
			;
		/* Set up address register */
		EEAR = Copy_u16Address + counter;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EERE);
		if (EEDR != (*(P_u8DataArray + counter)))//compare the value read to the value to be written
		{//if they are not equal then write the data
			EEDR = *(P_u8DataArray + counter);//move the data to EEDR

			/* Write logical one to EEMWE */
			EECR |= (1 << EEMWE);
			/* Start EEPROM write by setting EEWE */
			EECR |= (1 << EEWE);
		}
		else
		{

		}
		counter++;//increase bytes counter
	}
}

u8 EEPROM_u8ReadByte(const u16 Copy_u16Address)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
		;
	/* Set up address register */
	EEAR = Copy_u16Address;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_voidReadBlock(const u16 Copy_u16Address, u8* P_u8DataArray,const u16 Copy_u16Size)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
		;

	u16 counter = 0;//the counter of bytes that are read

	while (counter < Copy_u16Size) //loop until move all bytes to the given array
	{
		/* Set up address register */
		EEAR = Copy_u16Address + counter;
		/* Start EEPROM read by writing EERE */
		EECR |= (1 << EERE);
		/* move data from data register to the array */
		*(P_u8DataArray + counter) = EEDR;

		counter++;//increase the bytes counter
	}
}
