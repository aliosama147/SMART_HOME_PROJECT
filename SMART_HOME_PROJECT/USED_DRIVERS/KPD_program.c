#include "TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
u8 KPD_OutputNibble;
u8 KPD_InputNibble;

/*
USING: Initialize the lcd

Parameters : 1_ Port number of keypad 2_ Rows Nubble 3_ Columns Nibble

Return type : void

Return Value : NULL
*/

void KPD_vidInit(_enuGPIOx enuKPDPortNum,_enuNippleType enuKPDout,_enuNippleType enuKPDin){

    KPD_OutputNibble    =(enuKPDout==LOWNIBBLE)?LOWNIBBLE:HIGHNIBBLE;
    KPD_InputNibble     =(enuKPDout==LOWNIBBLE)?HIGHNIBBLE:LOWNIBBLE;
    DIO_vidSetNibbleMode(enuKPDPortNum,KPD_OutputNibble,OUTPUT);
    DIO_vidSetNibbleMode(enuKPDPortNum,KPD_InputNibble,INPUT);
    DIO_vidWriteNibble(enuKPDPortNum,KPD_InputNibble,HIGH);

}

/*
USING: Read Pressed Key in KEYPAD

Parameters : 1_ Port number of keypad 2_ Rows Nubble 3_ Columns Nibble

Return type : u8 ->> Char

Return Value : Key which pressed in keypad
*/

u8 KPD_u8GetKey(_enuGPIOx enuKPDPortNum){
	u8 key=NOT_PRESSED;
	u8 x='F';
    u8 arr[4][4]={
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'C','0','=','+'}
    };
	for(u8 i = 0; i < 4; i++)
	{
		DIO_vidWritePin(enuKPDPortNum,0,HIGH);
		DIO_vidWritePin(enuKPDPortNum,1,HIGH);
		DIO_vidWritePin(enuKPDPortNum,2,HIGH);
		DIO_vidWritePin(enuKPDPortNum,3,HIGH);
		DIO_vidWritePin(enuKPDPortNum,i,LOW);
		for(u8 j=0 ; j < 4; j++)
		{
			x = DIO_enuReadPin(enuKPDPortNum,(j+4));
			if(x==0)
			{
				key= arr[i][j];
				break;
			}
		}
		if(x==0)
		{
			break;
		}
	}
	return key;
}