/*
 * util.h
 *
 * Created: 8/11/2023 5:00:46 PM
 *  Author: user
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#define Set_Bit(reg, bit) (reg |= (1<<bit))
#define Clear_Bit(reg, bit) (reg &= ~(1<<bit))
#define Toggle_Bit(reg, bit) (reg ^= (1<<bit))
#define Read_Bit(reg, bit) ((reg >> bit) & 1)




#endif /* UTIL_H_ */