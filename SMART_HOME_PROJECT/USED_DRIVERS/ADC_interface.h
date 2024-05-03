#ifndef _MCAL_ADC_INTERFACE_H_
#define _MCAL_ADC_INTERFACE_H_
#include "TYPES.h"


// This enum used for the ADC PINS
typedef enum
{
    ADC_CHANNEL0 = 0,
    ADC_CHANNEL1 = 1,
    ADC_CHANNEL2 = 2,
    ADC_CHANNEL3 = 3,
    ADC_CHANNEL4 = 4,
    ADC_CHANNEL5 = 5,
    ADC_CHANNEL6 = 6,
    ADC_CHANNEL7 = 7
} _enuADCChannelNum;

// This Function Used to Initialize ADC
void ADC_vidInit(_enuADCChannelNum enuADCChannelNum);

// This Function to read a value from ADC
u16 ADC_u16Read(void);

#endif