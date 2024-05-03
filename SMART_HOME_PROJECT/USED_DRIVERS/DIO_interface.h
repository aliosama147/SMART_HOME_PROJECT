#ifndef _MCAL_DIO_INTERFACE_H_
#define _MCAL_DIO_INTERFACE_H_
#include "TYPES.h"

// This enum used for the General Purpose Registers

typedef enum
{
    GPIOA = 1,
    GPIOB,
    GPIOC,
    GPIOD
} _enuGPIOx;

// This enum used for the General Purpose Registers Pins

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
} _enuPinx;

// This enum used for the General Purpose Registers Pins mode

typedef enum
{
    INPUT = 0,
    OUTPUT

} _enuMode;

// This enum used for the General Purpose Registers Pins OUTPUT

typedef enum
{
    LOW = 0,
    HIGH

} _enuOutPut;

typedef enum {
    LOWNIBBLE =0,
    HIGHNIBBLE
} _enuNippleType;

// This Function Used to set the mode of pin in register
void DIO_vidSetPinMode(_enuGPIOx enuPortNum, _enuPinx enuPinNum, _enuMode enuMode);




// This Function Used to set the Value of pin in register
void DIO_vidWritePin(_enuGPIOx enuPortNum, _enuPinx enuPinNum, _enuOutPut enuOutPut);




// This Function Used to get the Value of pin in register and return type is HIGH or LOW
_enuOutPut DIO_enuReadPin(_enuGPIOx enuPortNum, _enuPinx enuPinNum);



// This Function Used to set the mode of the entire register
void DIO_vidSetPortMode(_enuGPIOx enuPortNum, u8 enuMode);



// This Function Used to set the value of the entire register in hex number or binary number
void DIO_vidWritePort(_enuGPIOx enuPortNum, u8 u8OutPut);




// This Function Used to set the mode of the high and low nibble of register
void DIO_vidSetNibbleMode(_enuGPIOx enuPortNum,_enuNippleType enuNibbleType, u8 u8Mode);



// This Function Used to set the value of the high and low nibble of register in hex number or binary number
void DIO_vidWriteNibble(_enuGPIOx enuPortNum,_enuNippleType enuNibbleType, u8 u8OutPut);


#endif