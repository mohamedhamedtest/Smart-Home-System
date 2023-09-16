/*
 * main.c
 *
 *  Created on: Sep 10, 2023
 *      Author: mohamed hamed
 */

//includes
#define F_CPU 8000000UL
#include "SPI_messages.h"
#include "app_configurations.h"
#include "../libs/STD_TYPES.h"
#include "../libs/util.h"
#include "../MCAL/Timers/TIMER.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/GIE/GIE.h"
#include "../MCAL/internal_EEPROM/EEPROM.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED/LED.h"
#include "../HAL/Servo_Motor/Servo_motor.h"
#include <avr/io.h>
#include <util/delay.h>

//ADMIN Password
u8 Global_u8StoredPass_ADMIN[PASS_SIZE]= {'1','2','3','4'};
//User Passwords
u8 Global_u8StoredPass_USER[PASS_SIZE]= {'1','1','1','1'};

//prototypes
//function to initialize all used peripherals
void init(void);
//welcome screen shown to user
void WelcomeScreen(void);
//void ADMIN_PasswordSetCheck(void);
//select ADMIN or User mode
void SelectMode(void);
//Check if password is correct or not
u8 CheckPassword(u8* EnteredPass, u8* StoredPass, u8 size);
//ADMIN's features list
void ADMIN_Menu(void);
//User's features list
void USER_Menu(void);
//void ADMIM_AddUser(void);
int main(void)
{
	init();
	WelcomeScreen();
	//ADMIN_PasswordSetCheck();
	while(1)
	{
		SelectMode();
	}
	return 0;
}

void init(void)
{
	GIE_voidEnable(); ////Global interrupt enable
	TIMER1_Init(); //Timer1 initialization
	SPI_vInitMaster(); //SPI master initialization
	SERVO_INIT(); //servo motor initialization
	KPD_INIT(); //keypad initialization
	LCD_INIT(); //LCD initialization
	//LED init
	LED_voidInit(ADMIN_LED_PORT, ADMIN_LED_PIN );
	LED_voidInit(USER_LED_PORT, USER_LED_PIN );
	LED_voidInit(BLOCKED_LED_PORT, BLOCKED_LED_PIN );

}

void WelcomeScreen(void)
{
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	SEND_A_STRING("Welcome to smart home system");
	LCD_CLEAR_ALL_SCREEN();
}


/*void ADMIN_PasswordSetCheck(void)
{
	u8 Local_u8KeyPressed, Local_u8Counter = 0;
	u8 Local_u8Array[PASS_SIZE] = {EMPTY,EMPTY,EMPTY,EMPTY};
	if(EEPROM_u8ReadByte(ADMIN_PASS_STATUS_ADDRESS) == PASS_FOUND)
	{
		//Do Nothing
	}
	else
	{
		LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		SEND_A_STRING("Set ADMIN pass: ");
		LCD_GOTO_XY(1,0);
		//looping until user enter all password digits
		while(Local_u8Counter < PASS_SIZE)
		{
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			//wait till user enter anything
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			//display num on lcd
			SEND_A_CHAR(Local_u8KeyPressed);
			//store digits of password in the array
			Local_u8Array[Local_u8Counter] = Local_u8KeyPressed;
			//increase counter to store next digit
			Local_u8Counter++;
		}
		//reset counter
		Local_u8Counter = 0;
		//set ADMIN password in EEPROM
		EEPROM_voidWriteBlock(EEPROM_ADMIN_ADDRESS,Local_u8Array, PASS_SIZE);
		//set ADMIN password status in EEPROM
		EEPROM_voidWriteByte(ADMIN_PASS_STATUS_ADDRESS, PASS_FOUND);
		LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
	}
}*/

void SelectMode(void)
{
	u8 Local_u8KeyPressed = KPD_NOT_PRESSED, Local_u8Counter = 0, Local_u8PassStatue, Local_u8PassAttempts = 0;
	u8 Local_u8EnteredPass[PASS_SIZE];
	Label1: LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	SEND_A_STRING("Choose Mode: ");
	LCD_GOTO_XY(1,0);
	SEND_A_STRING("1:ADMIN  2:USER");
	Local_u8KeyPressed = KPD_NOT_PRESSED;
	while(Local_u8KeyPressed == KPD_NOT_PRESSED)
	{
		Local_u8KeyPressed = KPD_GETKEY();
	}
	if(Local_u8KeyPressed == CHOOSE_ADMIN_MODE)
	{
		Label2: LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		SEND_A_STRING("Enter password:  ");
		LCD_GOTO_XY(1,0);
		//display cursor to assist user to enter password
		LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
		//looping until user enters password
		while(Local_u8Counter < PASS_SIZE)
		{
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			//wait till user enter anything
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			//display num on lcd
			SEND_A_CHAR(Local_u8KeyPressed);
			//store digits of password in the array
			Local_u8EnteredPass[Local_u8Counter] = Local_u8KeyPressed;
			//increase counter to store next digit
			Local_u8Counter++;
		}
		//remove cursor after entering password
		LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR_OFF);
		//check if password is correct
		Local_u8PassStatue = CheckPassword(Local_u8EnteredPass,Global_u8StoredPass_ADMIN, PASS_SIZE );
		//reset counter
		Local_u8Counter = 0;
		if(Local_u8PassStatue == CORRECT_PASS)
		{
			Local_u8PassAttempts = 0;
			ADMIN_Menu();
		}
		else
		{
			Local_u8PassAttempts++;
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			SEND_A_STRING("Wrong Password!");
			//if no password tries left the user will be blocked for specific time
			if(Local_u8PassAttempts >= PASS_ATTEMPTS)
			{
				LCD_CLEAR_ALL_SCREEN();
				LCD_GOTO_XY(0,0);
				SEND_A_STRING("No tries left");
				_delay_ms(3000);
				LCD_CLEAR_ALL_SCREEN();
				SEND_A_STRING("Blocked for");
				LCD_GOTO_XY(1,0);
				SEND_A_STRING("15 sec");
				//turn on blocked led for 10 sec then turn it off
				LED_voidTurnON(BLOCKED_LED_PORT, BLOCKED_LED_PIN);
				_delay_ms(5000);
				_delay_ms(5000);
				_delay_ms(5000);
				LED_voidTurnOFF(BLOCKED_LED_PORT, BLOCKED_LED_PIN);
				Local_u8PassAttempts = 0;
				goto Label1;
			}

			goto Label2;
		}
	}
	else if(Local_u8KeyPressed == CHOOSE_USER_MODE)
	{
		Label3: LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		SEND_A_STRING("Enter password:  ");
		LCD_GOTO_XY(1,0);
		//display cursor to assist user to enter password
		LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR);
		//looping until user enters password
		while(Local_u8Counter < PASS_SIZE)
		{
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			//wait till user enter anything
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			//display num on lcd
			SEND_A_CHAR(Local_u8KeyPressed);
			//store digits of password in the array
			Local_u8EnteredPass[Local_u8Counter] = Local_u8KeyPressed;
			//increase counter to store next digit
			Local_u8Counter++;
		}
		//remove cursor after entering password
		LCD_SEND_A_COMMAND(LCD_DISP_ON_CURSOR_OFF);
		//reset counter
		Local_u8Counter = 0;
		//check if password is correct
		Local_u8PassStatue = CheckPassword(Local_u8EnteredPass,Global_u8StoredPass_USER, PASS_SIZE );
		if(Local_u8PassStatue == CORRECT_PASS)
		{
			Local_u8PassAttempts = 0;
			USER_Menu();
		}
		else
		{
			Local_u8PassAttempts++;
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			SEND_A_STRING("Wrong Password!");
			//if no password tries left the user will be blocked for specific time
			if(Local_u8PassAttempts >= PASS_ATTEMPTS)
			{
				LCD_CLEAR_ALL_SCREEN();
				LCD_GOTO_XY(0,0);
				SEND_A_STRING("No tries left");
				_delay_ms(3000);
				LCD_CLEAR_ALL_SCREEN();
				SEND_A_STRING("Blocked for");
				LCD_GOTO_XY(1,0);
				SEND_A_STRING("15 sec");
				//turn on blocked led for 10 sec then turn it off
				LED_voidTurnON(BLOCKED_LED_PORT, BLOCKED_LED_PIN);
				_delay_ms(5000);
				_delay_ms(5000);
				_delay_ms(5000);
				LED_voidTurnOFF(BLOCKED_LED_PORT, BLOCKED_LED_PIN);
				Local_u8PassAttempts = 0;
				goto Label1;
			}
			goto Label3;
		}
	}
}

u8 CheckPassword(u8* EnteredPass, u8* StoredPass, u8 size)
{
	u8 Local_u8Counter = 0;
	while(Local_u8Counter < size)
	{
		//check that every entered digit is equal to the one stored in the EEPROM...
		if(*(EnteredPass + Local_u8Counter) != *(StoredPass + Local_u8Counter))
		{
			//if any number of them is wrong return wrong pass
			return WRONG_PASS;
		}
		//increase counter to store next digit
		Local_u8Counter++;
	}
	return CORRECT_PASS;
}

void ADMIN_Menu(void)
{
	u8 Local_u8KeyPressed = KPD_NOT_PRESSED, Local_u8DoorStatue = 0,Local_u8GarageStatue = 0, Local_u8LEDStatue = 0, Local_u8AirCondStatue = 0;
	//turn on ADMIN led
	LED_voidTurnON(ADMIN_LED_PORT, ADMIN_LED_PIN);
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	SEND_A_STRING("Welcome ADMIN");
	label4: LCD_CLEAR_ALL_SCREEN();
	SEND_A_STRING("1:Room1 2:Room2");
	LCD_GOTO_XY(1,0);
	SEND_A_STRING("3:Room3 4:more");
	Local_u8KeyPressed = KPD_NOT_PRESSED;
	while(Local_u8KeyPressed == KPD_NOT_PRESSED)
	{
		Local_u8KeyPressed = KPD_GETKEY();
	}
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	if(Local_u8KeyPressed == CHOOSE_ROOM1)
	{
		SPI_ui8TransmitRecive(ROOM1_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue: ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue: OFF");
		}
		else
		{
			SEND_A_STRING("Error");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM1_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM1_TURN_OFF);
		}
		goto label4;
	}
	else if(Local_u8KeyPressed == CHOOSE_ROOM2)
	{
		SPI_ui8TransmitRecive(ROOM2_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue: ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue: OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM2_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM2_TURN_OFF);
		}
		goto label4;

	}
	else if(Local_u8KeyPressed == CHOOSE_ROOM3)
	{
		SPI_ui8TransmitRecive(ROOM3_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue: ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue: OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM3_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM3_TURN_OFF);
		}
		goto label4;
	}
	else if(Local_u8KeyPressed == CHOOSE_MORE)
	{
		Label5: LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		SEND_A_STRING("1:A.C 2:Garage");
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("3:Door 4:Ret");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		if(Local_u8KeyPressed == CHOOSE_AIRCOND_ADMIN)
		{
			SPI_ui8TransmitRecive(AIR_COND_STATUS);
			_delay_ms(100);
			Local_u8AirCondStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
			if(Local_u8AirCondStatue == ON_STATUS)
			{
				SEND_A_STRING("A.C statue:ON");
			}
			else if(Local_u8AirCondStatue == OFF_STATUS)
			{
				SEND_A_STRING("A.C statue:OFF");
			}
			LCD_GOTO_XY(1,0);
			SEND_A_STRING("1:ON 2:OFF");
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			if(Local_u8KeyPressed == TURN_ON_AC)
			{
				SPI_ui8TransmitRecive(AIR_COND_TURN_ON);
			}
			else if(Local_u8KeyPressed == TURN_OFF_AC)
			{
				SPI_ui8TransmitRecive(AIR_COND_TURN_OFF);
			}
			goto Label5;

		}
		else if(Local_u8KeyPressed == CHOOSE_GARAGE)
		{

			Local_u8GarageStatue = GARAGE_STATUS();
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			if(Local_u8GarageStatue == GARAGE_CLOSED)
			{
				SEND_A_STRING("Statue: closed");
			}
			else if(Local_u8GarageStatue == GARAGE_OPEN)
			{
				SEND_A_STRING("Statue: opened");
			}
			LCD_GOTO_XY(1,0);
			SEND_A_STRING("1:Open 2:Close");
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			if(Local_u8KeyPressed == OPEN_GARAGE)
			{
				SERVO_OPEN_GARAGE();
				goto Label5;
			}
			else if(Local_u8KeyPressed == CLOSE_GARAGE)
			{
				SERVO_CLOSE_GARAGE();
				goto Label5;
			}
		}
		else if(Local_u8KeyPressed == CHOOSE_DOOR)
		{
			Local_u8DoorStatue = DOOR_STATUS();
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			if(Local_u8DoorStatue == DOOR_CLOSED)
			{
				SEND_A_STRING("Statue: closed");
			}
			else if(Local_u8DoorStatue == DOOR_OPEN)
			{
				SEND_A_STRING("Statue: opened");
			}
			LCD_GOTO_XY(1,0);
			SEND_A_STRING("1:Open 2:Close");
			Local_u8KeyPressed = KPD_NOT_PRESSED;
			while(Local_u8KeyPressed == KPD_NOT_PRESSED)
			{
				Local_u8KeyPressed = KPD_GETKEY();
			}
			if(Local_u8KeyPressed == OPEN_DOOR)
			{
				SERVO_OPEN_DOOR();
				goto Label5;
			}
			else if(Local_u8KeyPressed == CLOSE_DOOR)
			{
				SERVO_CLOSE_DOOR();
				goto Label5;
			}
		}
		else if(Local_u8KeyPressed == CHOOSE_RETURN)
		{
			goto label4;
		}

	}
}


/*void ADMIM_AddUser(void)
{
	u8 Local_u8Counter = 0, Local_u8KeyPressed, Local_u8Array[PASS_SIZE];
	if((EEPROM_u8ReadByte(GUEST1_PASS_STATUS_ADDRESS) == PASS_FOUND) && (EEPROM_u8ReadByte(GUEST2_PASS_STATUS_ADDRESS) == PASS_FOUND) && (EEPROM_u8ReadByte(GUEST3_PASS_STATUS_ADDRESS) == PASS_FOUND))
	{
		LCD_CLEAR_ALL_SCREEN();
		LCD_GOTO_XY(0,0);
		SEND_A_STRING("You can't add more users...");

	}
	else
	{
		if(EEPROM_u8ReadByte(GUEST1_PASS_STATUS_ADDRESS) != PASS_FOUND)
		{
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			SEND_A_STRING("Set user1 pass:");
			LCD_GOTO_XY(1,0);
			//looping until user enter all password digits
			while(Local_u8Counter < PASS_SIZE)
			{
				Local_u8KeyPressed = KPD_NOT_PRESSED;
				//wait till user enter anything
				while(Local_u8KeyPressed == KPD_NOT_PRESSED)
				{
					Local_u8KeyPressed = KPD_GETKEY();
				}
				//display num on lcd
				SEND_A_CHAR(Local_u8KeyPressed);
				//store digits of password in the array
				Local_u8Array[Local_u8Counter] = Local_u8KeyPressed;
				//increase counter to store next digit
				Local_u8Counter++;
			}
			//set ADMIN password in EEPROM
			EEPROM_voidWriteBlock(EEPROM_GUEST1_ADDRESS,Local_u8Array, PASS_SIZE);
			//set ADMIN password status in EEPROM
			EEPROM_voidWriteByte(GUEST1_PASS_STATUS_ADDRESS, PASS_FOUND);
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
		}
		else if(EEPROM_u8ReadByte(GUEST2_PASS_STATUS_ADDRESS) != PASS_FOUND)
		{
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			SEND_A_STRING("Set user2 pass:");
			LCD_GOTO_XY(1,0);
			//looping until user enter all password digits
			while(Local_u8Counter < PASS_SIZE)
			{
				Local_u8KeyPressed = KPD_NOT_PRESSED;
				//wait till user enter anything
				while(Local_u8KeyPressed == KPD_NOT_PRESSED)
				{
					Local_u8KeyPressed = KPD_GETKEY();
				}
				//display num on lcd
				SEND_A_CHAR(Local_u8KeyPressed);
				//store digits of password in the array
				Local_u8Array[Local_u8Counter] = Local_u8KeyPressed;
				//increase counter to store next digit
				Local_u8Counter++;
			}
			//set ADMIN password in EEPROM
			EEPROM_voidWriteBlock(EEPROM_GUEST2_ADDRESS,Local_u8Array, PASS_SIZE);
			//set ADMIN password status in EEPROM
			EEPROM_voidWriteByte(GUEST2_PASS_STATUS_ADDRESS, PASS_FOUND);
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
		}
		else if(EEPROM_u8ReadByte(GUEST3_PASS_STATUS_ADDRESS) != PASS_FOUND)
		{
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
			SEND_A_STRING("Set user2 pass:");
			LCD_GOTO_XY(1,0);
			//looping until user enter all password digits
			while(Local_u8Counter < PASS_SIZE)
			{
				Local_u8KeyPressed = KPD_NOT_PRESSED;
				//wait till user enter anything
				while(Local_u8KeyPressed == KPD_NOT_PRESSED)
				{
					Local_u8KeyPressed = KPD_GETKEY();
				}
				//display num on lcd
				SEND_A_CHAR(Local_u8KeyPressed);
				//store digits of password in the array
				Local_u8Array[Local_u8Counter] = Local_u8KeyPressed;
				//increase counter to store next digit
				Local_u8Counter++;
			}
			//set ADMIN password in EEPROM
			EEPROM_voidWriteBlock(EEPROM_GUEST3_ADDRESS,Local_u8Array, PASS_SIZE);
			//set ADMIN password status in EEPROM
			EEPROM_voidWriteByte(GUEST3_PASS_STATUS_ADDRESS, PASS_FOUND);
			LCD_CLEAR_ALL_SCREEN();
			LCD_GOTO_XY(0,0);
		}

	}

}*/

void USER_Menu(void)
{
	u8 Local_u8KeyPressed = KPD_NOT_PRESSED, Local_u8LEDStatue, Local_u8AirCondStatue;
	//turn on user led
	LED_voidTurnON(USER_LED_PORT, USER_LED_PIN);
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	SEND_A_STRING("Welcome user");
	label4: LCD_CLEAR_ALL_SCREEN();
	SEND_A_STRING("1:Room1 2:Room2");
	LCD_GOTO_XY(1,0);
	SEND_A_STRING("3:Room3 4:A.C");
	Local_u8KeyPressed = KPD_NOT_PRESSED;
	while(Local_u8KeyPressed == KPD_NOT_PRESSED)
	{
		Local_u8KeyPressed = KPD_GETKEY();
	}
	LCD_CLEAR_ALL_SCREEN();
	LCD_GOTO_XY(0,0);
	if(Local_u8KeyPressed == CHOOSE_ROOM1)
	{
		SPI_ui8TransmitRecive(ROOM1_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue:ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue:OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM1_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM1_TURN_OFF);
		}
		goto label4;
	}
	else if(Local_u8KeyPressed == CHOOSE_ROOM2)
	{
		SPI_ui8TransmitRecive(ROOM2_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue:ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue:OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM2_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM2_TURN_OFF);
		}
		goto label4;
	}
	else if(Local_u8KeyPressed == CHOOSE_ROOM3)
	{
		SPI_ui8TransmitRecive(ROOM3_STATUS);
		_delay_ms(100);
		Local_u8LEDStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8LEDStatue == ON_STATUS)
		{
			SEND_A_STRING("LED statue:ON");
		}
		else if(Local_u8LEDStatue == OFF_STATUS)
		{
			SEND_A_STRING("LED statue:OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_LED)
		{
			SPI_ui8TransmitRecive(ROOM3_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_LED)
		{
			SPI_ui8TransmitRecive(ROOM3_TURN_OFF);
		}
		goto label4;
	}
	else if(Local_u8KeyPressed == CHOOSE_AIRCOND_USER)
	{
		SPI_ui8TransmitRecive(AIR_COND_STATUS);
		_delay_ms(100);
		Local_u8AirCondStatue = SPI_ui8TransmitRecive(DEMAND_RESPONSE);
		if(Local_u8AirCondStatue == ON_STATUS)
		{
			SEND_A_STRING("A.C statue:ON");
		}
		else if(Local_u8AirCondStatue == OFF_STATUS)
		{
			SEND_A_STRING("A.C statue:OFF");
		}
		LCD_GOTO_XY(1,0);
		SEND_A_STRING("1:ON 2:OFF");
		Local_u8KeyPressed = KPD_NOT_PRESSED;
		while(Local_u8KeyPressed == KPD_NOT_PRESSED)
		{
			Local_u8KeyPressed = KPD_GETKEY();
		}
		if(Local_u8KeyPressed == TURN_ON_AC)
		{
			SPI_ui8TransmitRecive(AIR_COND_TURN_ON);
		}
		else if(Local_u8KeyPressed == TURN_OFF_AC)
		{
			SPI_ui8TransmitRecive(AIR_COND_TURN_OFF);
		}
		goto label4;
	}
}

