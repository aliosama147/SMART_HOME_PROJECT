#include "TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

void LED_vidInit(_enuGPIOx enuPortNum, _enuPinx enuPinNum)
{

    DIO_vidSetPinMode(enuPortNum, enuPinNum, OUTPUT);
}

void LED_vidLedOn(_enuGPIOx enuPortNum, _enuPinx enuPinNum)
{

    DIO_vidWritePin(enuPortNum, enuPinNum, HIGH);
}

void LED_vidLedOff(_enuGPIOx enuPortNum, _enuPinx enuPinNum)
{

    DIO_vidWritePin(enuPortNum, enuPinNum, LOW);
}

void LED_vidLedToggle(_enuGPIOx enuPortNum, _enuPinx enuPinNum)
{
    _enuOutPut enuOutPut;
    enuOutPut = DIO_enuReadPin(enuPortNum, enuPinNum);
    if (enuOutPut == HIGH)
    {
        LED_vidLedOff(enuPortNum, enuPinNum);
    }
    else
    {
        LED_vidLedOn(enuPortNum, enuPinNum);
    }
}
