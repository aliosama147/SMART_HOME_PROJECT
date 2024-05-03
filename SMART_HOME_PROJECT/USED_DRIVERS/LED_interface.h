#ifndef _HAL_LED_INTERFACE_H_
#define _HAL_LED_INTERFACE_H_

#include "DIO_interface.h"

void LED_vidInit(_enuGPIOx enuPortNum, _enuPinx enuPinNum);
void LED_vidLedOn(_enuGPIOx enuPortNum, _enuPinx enuPinNum);
void LED_vidLedOff(_enuGPIOx enuPortNum, _enuPinx enuPinNum);
void LED_vidLedToggle(_enuGPIOx enuPortNum, _enuPinx enuPinNum);

#endif