#ifndef  _MCAL_EEPROM_PRIVATE_H_
    #define _MCAL_EEPROM_PRIVATE_H_

//This macros for EEPROM registers in Atmega 32
#define EEARL  (*(volatile u8*) 0X3F)
#define EEARH  (*(volatile u8*) 0X3E)
#define EEDR   (*(volatile u8*) 0X3D)
#define EECR   (*(volatile u8*) 0X3C)

#define EERE    0
#define EEWE    1 
#define EEMWE   2
#define EERIE   3


#endif