/*
 * Servo_motor.h
 *
 *  Created on: Sep 10, 2023
 *      Author: user
 */

#ifndef HAL_SERVO_MOTOR_SERVO_MOTOR_H_
#define HAL_SERVO_MOTOR_SERVO_MOTOR_H_

//includes
#include "../../libs/STD_TYPES.h"
#include "../../libs/util.h"
#include "../../MCAL/Timers/TIMER.h"
#include "../../MCAL/DIO/DIO.h"

//configuration
#define DOOR_CLOSED    0
#define DOOR_OPEN      1

#define GARAGE_CLOSED  0
#define GARAGE_OPEN    1

//prototypes
void SERVO_INIT(void);
void SERVO_OPEN_DOOR(void);
void SERVO_CLOSE_DOOR(void);
void SERVO_OPEN_GARAGE(void);
void SERVO_CLOSE_GARAGE(void);
u8 DOOR_STATUS(void);
u8 GARAGE_STATUS(void);


#endif /* HAL_SERVO_MOTOR_SERVO_MOTOR_H_ */
