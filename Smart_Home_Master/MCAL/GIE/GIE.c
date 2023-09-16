/*
 * GIE.c
 *
 *  Created on: Aug 23, 2023
 *      Author: user
 */
#include"GIE.h"
#include "../../libs/util.h"
#include<avr/io.h>

void GIE_voidEnable(void)
{
	Set_Bit(SREG, SREG_I);
}

void GIE_voidDisable(void)
{
	Clear_Bit(SREG, SREG_I);
}
