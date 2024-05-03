#include "TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_private.h"
#include "LM35_config.h"

void LM35_vidInit(_enuADCChannelNum enuChannelNum)
{
    ADC_vidInit(enuChannelNum);
}


u8 LM35_u8LM35Read(void)
{

    u16 temp;
	u8 value;
    temp = ADC_u16Read();
 	value = (temp*(float)ADC_Vref)/10240;
    return value;
    
}