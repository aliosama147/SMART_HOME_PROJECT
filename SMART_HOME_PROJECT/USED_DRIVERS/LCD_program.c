#include "TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

#define F_CPU 8000000UL
#include <util/delay.h>

/*
USING: Initialize the lcd

Parameters : void

Return type : void

Return Value : NULL
*/

void LCD_vidInit()
{
    // Delay 200 ms to make lcd take its time to power on
    _delay_ms(200);         
    // Check If the lcd mode is 8-bit or 4-bit

    #if LCD_MODE    ==  1
    DIO_vidSetPortMode(LCD_DATA_PORT,OUTPUT);
    DIO_vidSetPinMode(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
    DIO_vidSetPinMode(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);
    DIO_vidSetPinMode(LCD_EN_PORT,LCD_EN_PIN,OUTPUT);
	 LCD_vidSendCmd(LCD_RETURN_HOME);
	 _delay_ms(50);
	 LCD_vidSendCmd(LCD_FUNCTION_8BIT_2LINES);
    #elif LCD_MODE  ==  0
    DIO_vidSetNibbleMode(LCD_DATA_PORT,LCD_NIBBLE_MODE,OUTPUT);
    DIO_vidSetPinMode(LCD_RS_PORT,LCD_RS_PIN,OUTPUT);
    DIO_vidSetPinMode(LCD_RW_PORT,LCD_RW_PIN,OUTPUT);
    DIO_vidSetPinMode(LCD_EN_PORT,LCD_EN_PIN,OUTPUT);
	 LCD_vidSendCmd(LCD_RETURN_HOME);
	 _delay_ms(50);
	 LCD_vidSendCmd(LCD_FUNCTION_4BIT_2LINES);
    #endif
    // Delay 50 ms To Send The Commands To LCD
    _delay_ms(2);
    LCD_vidSendCmd(LCD_DISP_ON_CURSOR_OFF);
    _delay_ms(2);
    LCD_vidSendCmd(LCD_CLEAR_SCREEN);
    _delay_ms(2);
	LCD_vidSendCmd(LCD_SHIFT_CURSOR_POS_LEFT);
	_delay_ms(2);

}


/*
USING: Send Command to lcd

Parameters : EnuCommands From LCD_config.h

Return type : void

Return Value : NULL
*/

void LCD_vidSendCmd(_enuLcdCmd enuCmd)
{
    DIO_vidWritePin(LCD_RS_PORT,LCD_RS_PIN,LOW);
    #if LCD_MODE    == 1
    DIO_vidWritePort(LCD_DATA_PORT,enuCmd);
    #elif LCD_MODE  ==  0
    DIO_vidWriteNibble(LCD_DATA_PORT,LCD_NIBBLE_MODE,(LCD_NIBBLE_MODE==HIGHNIBBLE)?enuCmd:enuCmd>>4);
	LCD_vidSendEnPulse();
    DIO_vidWriteNibble(LCD_DATA_PORT,LCD_NIBBLE_MODE,(LCD_NIBBLE_MODE==HIGHNIBBLE)?enuCmd<<4:enuCmd);
    #endif
    LCD_vidSendEnPulse(LCD_EN_PORT,LCD_EN_PIN);
}


/*
USING: Send Enable Pulse to lcd

Parameters : void

Return type : void

Return Value : NULL
*/
static void LCD_vidSendEnPulse()
{
    DIO_vidWritePin(LCD_EN_PORT,LCD_EN_PIN,HIGH);
    _delay_ms(10);
    DIO_vidWritePin(LCD_EN_PORT,LCD_EN_PIN,LOW);
}



/*
USING: Send Character to lcd

Parameters : u8Char ->>> Character in hex_number or Asci Code

Return type : void

Return Value : NULL
*/

void LCD_vidSendChar(u8 u8Char)
{
	DIO_vidWritePin(LCD_RS_PORT,LCD_RS_PIN,HIGH);
	#if LCD_MODE    == 1
	DIO_vidWritePort(LCD_DATA_PORT,u8Char);
	#elif LCD_MODE  ==  0
    DIO_vidWriteNibble(LCD_DATA_PORT,LCD_NIBBLE_MODE,(LCD_NIBBLE_MODE==HIGHNIBBLE)?u8Char:u8Char>>4);
    LCD_vidSendEnPulse();
    DIO_vidWriteNibble(LCD_DATA_PORT,LCD_NIBBLE_MODE,(LCD_NIBBLE_MODE==HIGHNIBBLE)?u8Char<<4:u8Char);
	#endif
	LCD_vidSendEnPulse(LCD_EN_PORT,LCD_EN_PIN);
}

/*
USING: Send Strings to lcd

Parameters : u8String ->>> String Pointer Contains More Than One Character

Return type : void

Return Value : NULL
*/

void LCD_vidSendString(u8* u8String)
{
	while((*u8String)!= '\0')
	{
		LCD_vidSendChar(*u8String);
		u8String++;
	}
}


/*
USING: Send Number to lcd

Parameters : u32Num ->>> Unsigned Integar Number

Return type : void

Return Value : NULL
*/

void LCD_vidSendNumber(u32 u32Num){
	u8 str[20];
	sprintf(str,"%d",u32Num);
	LCD_vidSendString(str);
}


/*
USING: Send Number to lcd

Parameters : f32Num ->>> Float , Negative OR positive numbers

Return type : void

Return Value : NULL
*/

void LCD_vidWriteRealNumber(float f32Num)
{
	LCD_vidSendString(((f32Num<0)?"-":""));
	float fNum=(f32Num<0)?-f32Num:f32Num;
	LCD_vidSendNumber(fNum);
	u32 num=(fNum*(10)*LCD_REAL_NUMBER_DIGITS_AFTER_DOT);
	num %=(10)*LCD_REAL_NUMBER_DIGITS_AFTER_DOT;
	if(num>0){
		LCD_vidSendString(".");
		LCD_vidSendNumber(num);
	}
}


/*
USING: Change Position of the cursor

Parameters : 1_ u8Line ->>> line number 2_ u8Position ->>> position number

Return type : void

Return Value : NULL
*/


void LCD_vidMoveCursor(u8 u8Line, u8 u8Position)
{
	if(u8Line < 1 || u8Line > 2 || u8Position < 1 ||u8Position > 16)
	{
        LCD_vidSendCmd(0x80);
	}
	else if(u8Line == 1)
	{
        LCD_vidSendCmd(0x80 +(u8Position - 1));
	}
	else if(u8Line == 2)
	{
        LCD_vidSendCmd(0xC0 +(u8Position - 1));
	}
	
	_delay_ms(1);
}
