#ifndef  _MCAL_DIO_PRIVATE_H_
    #define _MCAL_DIO_PRIVATE_H_


//This macros for PORTA in Atmega 32
#define PINA  (*(volatile u8*) 0x39)
#define DDRA  (*(volatile u8*) 0x3A)
#define PORTA (*(volatile u8*) 0x3B)


//This macros for PORTB in Atmega 32
#define PINB  (*(volatile u8*) 0x36)
#define DDRB  (*(volatile u8*) 0x37)
#define PORTB (*(volatile u8*) 0x38)


//This macros for PORTC in Atmega 32
#define PINC  (*(volatile u8*) 0x33)
#define DDRC  (*(volatile u8*) 0x34)
#define PORTC (*(volatile u8*) 0x35)


//This macros for PORTD in Atmega 32
#define PIND  (*(volatile u8*) 0x30)
#define DDRD  (*(volatile u8*) 0x31)
#define PORTD (*(volatile u8*) 0x32)


#endif