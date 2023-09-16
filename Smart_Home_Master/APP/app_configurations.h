/*
 * main_configuration.h
 *
 *  Created on: Sep 10, 2023
 *      Author: user
 */

#ifndef APP_APP_CONFIGURATIONS_H_
#define APP_APP_CONFIGURATIONS_H_

//includes
#include "../libs/STD_TYPES.h"

//modes
#define ADMIN_MODE     1
#define USER_MODE      2

//Password
#define PASS_SIZE      4
#define PASS_ATTEMPTS  3

//EEPROM
//check password is set or not
#define PASS_FOUND      (u16)0x01
#define PASS_NOT_FOUND  (u16)0xFF

#define PASS_SET        1
#define PASS_NOT_SET    0

#define CORRECT_PASS    1
#define WRONG_PASS      0

//passwords addresses
#define ADMIN_PASS_STATUS_ADDRESS   (u16)0x50
#define GUEST_PASS_STATUS_ADDRESS   (u16)0x51
#define EEPROM_ADMIN_ADDRESS        (u16)0x100
#define EEPROM_GUEST_ADDRESS        (u16)0x104
#define LOGIN_BLOCKED_ADDRESS       (u16)0x108

//Choices from LCD using Keypad
#define CHOOSE_ADMIN_MODE  '1'
#define CHOOSE_USER_MODE   '2'

#define CHOOSE_ROOM1       '1'
#define CHOOSE_ROOM2       '2'
#define CHOOSE_ROOM3       '3'
#define CHOOSE_MORE        '4'

#define CHOOSE_AIRCOND_ADMIN     '1'
#define CHOOSE_AIRCOND_USER      '4'
#define CHOOSE_GARAGE     		 '2'
#define CHOOSE_DOOR              '3'
#define CHOOSE_RETURN            '4'

#define OPEN_DOOR          '1'
#define CLOSE_DOOR         '2'

#define OPEN_GARAGE        '1'
#define CLOSE_GARAGE       '2'

#define TURN_ON_LED        '1'
#define TURN_OFF_LED       '2'

#define TURN_ON_AC         '1'
#define TURN_OFF_AC        '2'

//LED
#define ADMIN_LED_PORT      DIO_PORTB
#define USER_LED_PORT       DIO_PORTB
#define BLOCKED_LED_PORT    DIO_PORTB

#define ADMIN_LED_PIN      DIO_PIN0
#define USER_LED_PIN       DIO_PIN1
#define BLOCKED_LED_PIN    DIO_PIN2


#endif /* APP_APP_CONFIGURATIONS_H_ */
