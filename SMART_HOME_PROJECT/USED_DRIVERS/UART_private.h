#ifndef  _MCAL_UART_PRIVATE_H_
    #define _MCAL_UART_PRIVATE_H_

//  UART Registers

    #define UDR    		(*(volatile u8*)0x2C)
    #define USCRA    	(*(volatile u8*)0x2B)
    #define USCRB    	(*(volatile u8*)0x2A)
	#define USCRC  		(*(volatile u8*)0x40)
	#define UBRRL  		(*(volatile u8*)0x29)
	#define UBRRH  		(*(volatile u8*)0x40)
	

 // PINS of USCRA  

	#define MPCM 	0
	#define U2X 	1
	#define PE 		2
	#define DOR 	3
	#define FE 		4
	#define USRE 	5
	#define TXC 	6
	#define RXC 	7


// PINS of USCRB

	#define TXBB  	0
	#define RXBB  	1
	#define UCSZ2  	2
	#define TXEN 	3
	#define RXEN 	4
	#define UDRIE 	5
	#define TXCIE 	6
	#define RXCIE  	7


// PINS of USCRC

	#define UCPOL    0
	#define UCSZ0    1
	#define UCSZ1    2
	#define USBS     3
	#define UPM0     4
	#define UPM1     5
	#define UMSEL    6
	#define URSEL    7


#endif