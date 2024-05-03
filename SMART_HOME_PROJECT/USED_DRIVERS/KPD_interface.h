#ifndef _HAL_KPD_INTERFACE_H_
#define _HAL_KPD_INTERFACE_H_

#include "DIO_interface.h"
#define NOT_PRESSED 'F'
// This Function Used to Initialize KeyPad
void KPD_vidInit(_enuGPIOx enuKPDPortNum,_enuNippleType enuKPDout,_enuNippleType enuKPDin);

// This Function Used to Initialize KeyPad
u8 KPD_u8GetKey(_enuGPIOx enuKPDPortNum);

#endif