

#include "TYPES.h"
#include "BIT_MATH.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

/*
USING: set the mode of the Pin

Parameters : 1_ Port number 2_ Pin number 3_ The Mode from [OUTPUT , INPUT] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used The macro SET_BIT ( in the config file of DIO )

*/

void EEPROM_vidWrite(u16 u16Address , u8 u8Data)
{
	u16Address &=0x03FF;
    EEARH   = (u8) (u16Address); 
    EEARL   = (u8) u16Address>>8; 
    EEDR    = u8Data;
	SET_BIT(EECR, EEMWE);
	SET_BIT(EECR, EEWE);
    while(GET_BIT(EECR,EEWE));
}


/*
USING: set the mode of the Pin

Parameters : 1_ Port number 2_ Pin number 3_ The Mode from [OUTPUT , INPUT] or Hex_number and Binary Number

Return type : void

Return Value : NULL

HOW to work :

Using Switch case for the port number in parameters we can know the port number so we used The macro SET_BIT ( in the config file of DIO )

*/

u8 EEPROM_u8Read(u16 u16Address)
{
    u16Address &=0X03FF;
    EEARH = (u8) (u16Address);
	EEARL = (u8) u16Address >> 8 ;
	SET_BIT(EECR, EERE);
	return EEDR;
}