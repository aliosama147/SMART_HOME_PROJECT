#ifndef _HAL_LCD_INTERFACE_H_
#define _HAL_LCD_INTERFACE_H_

#include "DIO_interface.h"


// This enum used To define The Commands Hex-Numbers

typedef enum {

 LCD_CLEAR_SCREEN		        =   0x01,
 LCD_RETURN_HOME		        =   0x02,
 LCD_SHIFT_CURSOR_LEFT		    =   0x04,
 LCD_SHIFT_DISPLAY_RIGHT 	    =   0x05,
 LCD_SHIFT_CURSOR_RIGHT		    =   0x06,
 LCD_SHIFT_DISPLAY_LEFT		    =   0x07,
 LCD_DISP_OFF_CURSOR_OFF        =   0x08,
 LCD_DISP_OFF_CURSOR_ON         =   0x0A,
 LCD_DISP_ON_CURSOR_OFF         =   0x0C,
 LCD_DISP_ON_CURSOR_ON          =   0x0E,
 LCD_DISP_ON_CURSOR_BLINK       =   0x0F,
 LCD_SHIFT_CURSOR_POS_LEFT	    =   0x10,
 LCD_SHIFT_CURSOR_POS_RIGHT	    =   0x14,
 LCD_SHIFT_ENTIRE_DISPLAY_LEFT	=   0x18,
 LCD_SHIFT_ENTIRE_DISPLAY_RIGHT	=   0x1C,
 LCD_CURSOR_POS_FIRST_LINE	    =   0x80,
 LCD_CURSOR_POS_SECOND_LINE	    =   0xC0,
 LCD_FUNCTION_8BIT_2LINES       =   0x38,
 LCD_FUNCTION_4BIT_2LINES       =   0x28

}_enuLcdCmd;

// This Function Used to Initialize LCD MC
void LCD_vidInit();


// This Function Used to Send Commands to LCD MC
void LCD_vidSendCmd(_enuLcdCmd enuCmd);

// This Function Used to Print characters on LCD MC
void LCD_vidSendChar(u8 enuChar);

// This Function Used to Print Strings on LCD MC
void LCD_vidSendString(u8* u8String);

// This Function Used to Print Numbers on LCD MC
void LCD_vidSendNumber(u32 u32Num);

// This Function Used to Print Float , Negative and positive numbers on LCD MC
void LCD_vidWriteRealNumber(float f32Num);

// This Function Used to Move Cursor Of LCD
void LCD_vidMoveCursor(u8 u8Line, u8 u8Position);
#endif