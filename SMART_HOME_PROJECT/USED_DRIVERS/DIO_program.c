

#include "TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

/*
USING: set the mode of the Pin

Parameters : 1_ Port number 2_ Pin number 3_ The Mode from [OUTPUT , INPUT] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used The macro SET_BIT ( in the config file of DIO )

*/

void DIO_vidSetPinMode(_enuGPIOx enuPortNum , _enuPinx enuPinNum   , _enuMode enuMode){
    switch (enuPortNum){
        case GPIOA :    
                if(enuMode == OUTPUT)
                {
                    SET_BIT(DDRA,enuPinNum);
                }else{
                    CLR_BIT(DDRA,enuPinNum);
                }
                break;
        case GPIOB :    
                if(enuMode == OUTPUT)
                {
                    SET_BIT(DDRB,enuPinNum);
                }else{
                    CLR_BIT(DDRB,enuPinNum);
                }
                break;

        case GPIOC :    
                if(enuMode == OUTPUT)
                {
                    SET_BIT(DDRC,enuPinNum);
                }else{
                    CLR_BIT(DDRC,enuPinNum);
                }
                break;
        case GPIOD :    
                if(enuMode == OUTPUT)
                {
                    SET_BIT(DDRD,enuPinNum);
                }else{
                    CLR_BIT(DDRD,enuPinNum);
                }
                break;
        
    }

}


/*
USING: set the value of the pin

Parameters : 1_ Port number 2_ Pin number 3_ The Output value from [HIGH , LOW] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used the macro SET_BIT ( in the config file in DIO )

*/

void DIO_vidWritePin(_enuGPIOx enuPortNum   , _enuPinx enuPinNum   , _enuOutPut enuOutPut){

  switch (enuPortNum){

        case GPIOA :    
                if(enuOutPut == HIGH)
                {
                    SET_BIT(PORTA,enuPinNum);
                }else{
                    CLR_BIT(PORTA,enuPinNum);
                }
                break;
        case GPIOB :    
                if(enuOutPut == HIGH)
                {
                    SET_BIT(PORTB,enuPinNum);
                }else{
                    CLR_BIT(PORTB,enuPinNum);
                }
                break;

        case GPIOC :    
                if(enuOutPut == HIGH)
                {
                    SET_BIT(PORTC,enuPinNum);
                }else{
                    CLR_BIT(PORTC,enuPinNum);
                }
                break;
        case GPIOD :    
                if(enuOutPut == HIGH)
                {
                    SET_BIT(PORTD,enuPinNum);
                }else{
                    CLR_BIT(PORTD,enuPinNum);
                }
                break;
        
    }

}

/*
USING: get the value of the register

Parameters : 1_ Port number 2_Pin Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used the macro GET_BIT ( in the config file in DIO )

*/

_enuOutPut  DIO_enuReadPin(_enuGPIOx enuPortNum   , _enuPinx enuPinNum){

    _enuOutPut enuOutPut;
    
    switch (enuPortNum){

        case GPIOA :    
                enuOutPut=  GET_BIT(PINA,enuPinNum);
                break;

        case GPIOB :
                enuOutPut=  GET_BIT(PINB,enuPinNum);
                break;

        case GPIOC :
               enuOutPut=   GET_BIT(PINC,enuPinNum);
               break;

        case GPIOD :
               enuOutPut=   GET_BIT(PIND,enuPinNum);
                break;
        default:
                    break;
        
    }
    return enuOutPut;
}



/*
USING: set the mode of the register

Parameters : 1_ Port number 2_ The Mode from [OUTPUT , INPUT] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port unmber in parameters we can know the port number so we used The macro set in the config file of DIO

*/


void DIO_vidSetPortMode(_enuGPIOx enuPortNum  , u8 u8Mode){

    switch (enuPortNum){

        case GPIOA :    
                if(u8Mode == OUTPUT)
                {
                    DDRA=0XFF; // set all pins as output
                }else if(u8Mode == INPUT){
					DDRA = 0X00;// set all pins as input
                }else{
					DDRA = u8Mode; // pins mode depends on u8Mode
				}
                break;
        case GPIOB :    
                if(u8Mode == OUTPUT)
                {
                    DDRB=0XFF;
                }else if(u8Mode == INPUT){
					DDRB = 0X00;
                }else{
					DDRB = u8Mode;
                }
                break;

        case GPIOC :    
                if(u8Mode == OUTPUT)
                {
                    DDRC=0XFF;
                }else if(u8Mode == INPUT){
					DDRC = 0X00;
                }else{
					DDRC = u8Mode;
                }
                break;
        case GPIOD :    
                if(u8Mode == OUTPUT)
                {
                    DDRD=0XFF;
                }else if(u8Mode == INPUT){
					DDRD = 0X00;
                }else{
					DDRD = u8Mode;
                }
                break;
        
    }


}




/*
USING: set the value of the register

Parameters : 1_ Port number 2_ The Output value from [HIGH , LOW] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port unmber in parameters we can know the port number so we used the macro set in the config file in DIO

*/


void DIO_vidWritePort(_enuGPIOx enuPortNum    , u8 u8OutPut){

  switch (enuPortNum){

        case GPIOA :    
                if(u8OutPut == HIGH)
                {
                    PORTA =0XFF; // write HIGH on all pins of the port
                }else if(u8OutPut == LOW){
                    PORTA =0X00;// write LOW on all pins of the port
                }else{
                    PORTA=u8OutPut; // all pins values of the port depends on the u8Output
                }
                break;
        case GPIOB :    
                if(u8OutPut == HIGH)
                {
                    PORTB =0XFF;
                }else if(u8OutPut == LOW){
                    PORTB =0X00;
                }else{
                    PORTB=u8OutPut;
                }
                break;

        case GPIOC :    
                if(u8OutPut == HIGH)
                {
                    PORTC =0XFF;
                }else if(u8OutPut == LOW){
                    PORTC =0X00;
                }else{
                    PORTC=u8OutPut;
                }
                break;
        case GPIOD :    
                if(u8OutPut == HIGH)
                {
                    PORTD =0XFF;
                }else if(u8OutPut == LOW){
                    PORTD =0X00;
                }else{
                    PORTD=u8OutPut;
                }
                break;
        
    }


}




/*
USING: set the mode of the high and low nibble of the register

Parameters : 1_ Port number 2_ The Mode from [OUTPUT , INPUT] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port unmber in parameters we can know the port number so we used the function of DIO_vidSetPortMode 

    In HIGH nibble:  we set 0xAB ===> A is the Mode we set in the high nibble 
        , B is the Mode Was found in the port before set the Mode to save it

    In LOW nibble:  we set 0xAB  ===> A  is the Mode Was found in the HIGH nibble before set the Mode to save it  
        , B is the Mode we set in the low nibble 

*/


void DIO_vidSetNibbleMode(_enuGPIOx enuPortNum,_enuNippleType enuNibbleType, u8 u8Mode){
	switch (enuPortNum){
		case GPIOA :
            if(enuNibbleType==HIGHNIBBLE){ // if we want to write in high nibble
                // (u8Mode & 0X0F)  to get the high nibble of the u8Mode
                // (DDRA & 0XF0)    to get the Low nibble of the Register
                //  to keep low nibble values we use OR operator between them
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0XF0) | (DDRA & 0X0F) ) ); 

            }else{  // if we want to write in low nibble
                // (u8Mode & 0X0F)  to get the low nibble of the u8Mode
                // (DDRA & 0XF0)    to get the High nibble of the Register
                //  to keep High nibble values we use OR operator between them
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0X0F) | (DDRA & 0XF0) ) );
            }
			break;
		case GPIOB :
			if(enuNibbleType==HIGHNIBBLE){
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0XF0) | (DDRB & 0X0F) ) );

            }else{
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0X0F) | (DDRB & 0XF0) ) );
            }
			break;
		case GPIOC :
			if(enuNibbleType==HIGHNIBBLE){
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0XF0) | (DDRC & 0X0F) ) );

            }else{
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0X0F) | (DDRC & 0XF0) ) );
            }
			break;
		case GPIOD :
			if(enuNibbleType==HIGHNIBBLE){
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0XF0) | (DDRD & 0X0F) ) );

            }else{
                DIO_vidSetPortMode(enuPortNum  , ( (u8Mode & 0X0F) | (DDRD & 0XF0) ) );
            }
		break;
	}
	
	
}




/*
USING: set the value of the high and low nibble of the register

Parameters : 1_ Port number      2_ Nibble Type       3_ The Output value from [HIGH , LOW] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used the function of DIO_vidWritePort

    In HIGH nibble:  we set 0xAB ===> A is the value we set in the high nibble 
        , B is the value Was found in the port before set the value to save it

    In LOW nibble:  we set 0xAB  ===> A  is the value Was found in the HIGH nibble before set the value to save it  
        , B is the value we set in the low nibble 

*/


void DIO_vidWriteNibble(_enuGPIOx enuPortNum,_enuNippleType enuNibbleType, u8 u8OutPut)
{
	switch (enuPortNum){
		case GPIOA :
            if(enuNibbleType==HIGHNIBBLE){  
                // if we want to write in HIGH nibble
                // (u8Mode & 0XF0)  to get the HIGH nibble of the u8Mode
                // (PORTA & 0X0F)    to get the LOW nibble of the Register
                //  to keep LOW nibble values we use OR operator between them
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0XF0) | (PORTA & 0X0F) ) );

            }else{  
                // if we want to write in low nibble
                // (u8Mode & 0X0F)  to get the low nibble of the u8Mode
                // (PORTA & 0XF0)    to get the High nibble of the Register
                //  to keep High nibble values we use OR operator between them
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0X0F) | (PORTA & 0XF0) ) );
            }
            break;
		case GPIOB :
            if(enuNibbleType==HIGHNIBBLE){
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0XF0) | (PORTB & 0X0F) ) );
            }else{
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0X0F) | (PORTB & 0XF0) ) );
            }
            break;
        case GPIOC :
            if(enuNibbleType==HIGHNIBBLE){
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0XF0) | (PORTC & 0X0F) ) );
            }else{
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0X0F) | (PORTC & 0XF0) ) );
            }
            break;
        case GPIOD :
            if(enuNibbleType==HIGHNIBBLE){
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0XF0) | (PORTD & 0X0F) ) );
            }else{
                DIO_vidWritePort(enuPortNum		, ( (u8OutPut & 0X0F) | (PORTD & 0XF0) ) );
            }
            break;
		break;
	}
}
