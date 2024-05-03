#ifndef _MCAL_ADC_CONFIG_H_
    #define _MCAL_ADC_CONFIG_H_
/*
Options of ADC_STORE_MODE :
    0 => 2 Bits in ADCH
    1 => 8 Bits in ADCH
*/

#define ADC_STORE_MODE   0 



/*
Options of ADC_PRESCALER :
    0 => Prescaler 2
    2 => Prescaler 4
    3 => Prescaler 8
    4 => Prescaler 16
    5 => Prescaler 32
    6 => Prescaler 64
    7 => Prescaler 128
*/
#define ADC_PRESCALER  6


/*
Options for ADC_VOLT_REF :
    0 => Select External Aref and Stop Internal Aref
    1 => Select Avcc and 5V     Internal Aref With External Capacitor on Aref
    3 => Select Avcc and 2.56V  Internal Aref With External Capacitor on Aref

*/
#define ADC_VOLT_REF  3



#endif