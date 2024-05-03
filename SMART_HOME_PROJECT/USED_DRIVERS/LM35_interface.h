#ifndef _HAL_LM35_INTERFACE_H_
#define _HAL_LM35_INTERFACE_H_

#include "ADC_interface.h"

void LM35_vidInit(_enuADCChannelNum enuChannelNum);
u8 LM35_u8LM35Read(void);

#endif