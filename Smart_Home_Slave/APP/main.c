
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../libs/STD_TYPES.h"
#include "../libs/util.h"
#include "../MCAL/Timers/TIMER.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/GIE/GIE.h"
#include "../HAL/LED/LED.h"
#include "SPI_messages.h"
#include "app_configurations_slave.h"

// the required temperature which sent from Master with initial value 24
volatile u16 required_temperature=24;
// the temperature of the room
volatile u16 temp_sensor_reading=0;
//the counter which determine the periodic time of implementing ISR
volatile u8 counter=0;
//last air conditioning value which will help in hysteresis
volatile u8 Last_AIR_COND_value = AIR_CONDTIONING_OFF;

int main(void)
{
	GIE_voidEnable();
	ADC_voidInit();
	TIMER0_Init();

	//initialize the SPI as a slave
	SPI_vInitSlave();

	/* initialization of output pins of connected leds or devices */
	LED_voidInit(AIR_COND_PORT,AIR_COND_PIN);
	LED_voidInit(ROOM1_PORT,ROOM1_PIN);
	LED_voidInit(ROOM2_PORT,ROOM2_PIN);
	LED_voidInit(ROOM3_PORT,ROOM3_PIN);

	u8 request = DEFAULT_ACK;//the value that is received from the master

	while(1)
	{
		request = SPI_ui8TransmitRecive(DEFAULT_ACK);//wait for the master to start the transmitting
		switch (request)
		{
		//commands related to send the current status back to the master
		case ROOM1_STATUS:
			if (LED_u8CheckStatus(ROOM1_PORT,ROOM1_PIN)== 0)//if the led is turned off
			{
				SPI_ui8TransmitRecive(OFF_STATUS);
			}
			else if (LED_u8CheckStatus(ROOM1_PORT,ROOM1_PIN)== 1)//if the led is turned on
			{
				SPI_ui8TransmitRecive(ON_STATUS);
			}

			break;//break the switch case
		case ROOM2_STATUS:
			if (LED_u8CheckStatus(ROOM2_PORT,ROOM2_PIN)== 0)//if the led is turned off
			{
				SPI_ui8TransmitRecive(OFF_STATUS);
			}
			else if (LED_u8CheckStatus(ROOM2_PORT,ROOM2_PIN)== 1)//if the led is turned on
			{
				SPI_ui8TransmitRecive(ON_STATUS);
			}
			break;//break the switch case
		case ROOM3_STATUS:
			if (LED_u8CheckStatus(ROOM3_PORT,ROOM3_PIN)== 0)//if the led is turned off
			{
				SPI_ui8TransmitRecive(OFF_STATUS);
			}
			else if (LED_u8CheckStatus(ROOM3_PORT,ROOM3_PIN)== 1)//if the led is turned on
			{
				SPI_ui8TransmitRecive(ON_STATUS);
			}
			break;//break the switch case
		case AIR_COND_STATUS:
			if (LED_u8CheckStatus(AIR_COND_PORT,AIR_COND_PIN)== 0)//if the led is turned off
			{
				SPI_ui8TransmitRecive(OFF_STATUS);
			}
			else if (LED_u8CheckStatus(AIR_COND_PORT,AIR_COND_PIN)== 1)//if the led is turned on
			{
				SPI_ui8TransmitRecive(ON_STATUS);
			}
			break;

		case ROOM1_TURN_ON:
			LED_voidTurnON(ROOM1_PORT,ROOM1_PIN);//turn on the led of room 1
			break;//break the switch case
		case ROOM2_TURN_ON:
			LED_voidTurnON(ROOM2_PORT,ROOM2_PIN);//turn on the led of room 2
			break;//break the switch case
		case ROOM3_TURN_ON:
			LED_voidTurnON(ROOM3_PORT,ROOM3_PIN);//turn on the led of room 3
			break;//break the switch case
		case AIR_COND_TURN_ON:
			TIMER0_Init();
			LED_voidTurnON(AIR_COND_PORT,AIR_COND_PIN);//turn on the led of air conditioning
			break;//break the switch case

		case ROOM1_TURN_OFF:
			LED_voidTurnOFF(ROOM1_PORT,ROOM1_PIN);//turn off the led of room 1
			break;//break the switch case
		case ROOM2_TURN_OFF:
			LED_voidTurnOFF(ROOM2_PORT,ROOM2_PIN);//turn off the led of room 2
			break;//break the switch case
		case ROOM3_TURN_OFF:
			LED_voidTurnOFF(ROOM3_PORT,ROOM3_PIN);//turn off the led of room 3
			break;//break the switch case
		case AIR_COND_TURN_OFF:
			TIMER0_STOP();
			LED_voidTurnOFF(AIR_COND_PORT,AIR_COND_PIN);//turn off the led of air conditioning
			break;//break the switch case
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	counter++;//count the ticks of the timer zero
	if(counter>=10)//do that code every 10 ticks
	{
		counter=0;//clear the counter of ticks
		temp_sensor_reading=(0.25 * ADC_u8GetChannelReading());//read the temperature from the temperature sensor connected to the ADC of the micro controller
		if (temp_sensor_reading>=(required_temperature+1))//do that code if the read temperature if greater than required temperature by one or more
		{
			LED_voidTurnON(AIR_COND_PORT,AIR_COND_PIN);//turn on the led of the air conditioning
			Last_AIR_COND_value = AIR_CONDTIONING_ON;
		}
		else if (temp_sensor_reading<=(required_temperature-1))//do that code if the read temperature if lesser than required temperature by one or more
		{
			LED_voidTurnOFF(AIR_COND_PORT,AIR_COND_PIN);//turn off the led of the air conditioning
			Last_AIR_COND_value = AIR_CONDTIONING_OFF;
		}
		else if(temp_sensor_reading == required_temperature)
		{
			if (Last_AIR_COND_value==AIR_CONDTIONING_ON)//in the case of the last saved status of the air conditioning was on
			{
				LED_voidTurnON(AIR_COND_PORT,AIR_COND_PIN);//turn on the led of the air conditioning
			}
			else if (Last_AIR_COND_value==AIR_CONDTIONING_OFF)//in the case of the last saved status of the air conditioning was off
			{
				LED_voidTurnOFF(AIR_COND_PORT,AIR_COND_PIN);//turn off the led of the air conditioning
			}
		}
	}
}
