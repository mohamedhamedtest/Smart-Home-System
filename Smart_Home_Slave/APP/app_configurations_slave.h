/*
 *  app_configurations_slave.h
 *

 *  Author: user
 */


#ifndef APP_CONFIGURATION_SLAVE_H_
#define APP_CONFIGURATION_SLAVE_H_
#include "../libs/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"

#define AIR_CONDTIONING_ON          (u8)0x01
#define AIR_CONDTIONING_OFF			(u8)0x00

#define AIR_COND_PIN				DIO_PIN0
#define ROOM1_PIN					DIO_PIN1
#define ROOM2_PIN					DIO_PIN2
#define ROOM3_PIN					DIO_PIN3

#define AIR_COND_PORT 				DIO_PORTD
#define ROOM1_PORT    				DIO_PORTD
#define ROOM2_PORT   				DIO_PORTD
#define ROOM3_PORT   				DIO_PORTD

#endif /* APP_CONFIGURATION_SLAVE_H_ */
