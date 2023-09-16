/*
 * EEPROM.h
 *
 *  Created on: Sep 9, 2023
 *      Author: user
 */

#ifndef EEPROM_H_
#define EEPROM_H_

//includes
#include "../../libs/STD_TYPES.h"
#include "../../libs/util.h"
//prototypes
//write byte to EEPROM
void EEPROM_voidWriteByte( const u16 Copy_u16Address, const u8 Copy_u8Data);
//write block to EEPROM
void EEPROM_voidWriteBlock( const u16 Copy_u16Address, const u8* P_u8DataArray, const u16 Copy_u16Size);
//read byte from EEPROM
u8 EEPROM_u8ReadByte( const u16 Copy_u16Address);
//read block from EEPROM
void EEPROM_voidReadBlock( const u16 Copy_u16Address, u8* P_u8DataArray, const  u16 Copy_u16Size);

#endif /* EEPROM_H_ */
