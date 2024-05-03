#ifndef _MCAL_UART_CONFIG_H_
    #define _MCAL_UART_CONFIG_H_

/*
Options of USART_MODE :
        0 => Asynchronous Normal mode
        1 => Synchronous mode
        2 => Asynchronous Double Speed mode
*/
#define USART_MODE   0 


/*
Options of USART_PARITY :

        0 => Even Parity
        1 => Odd  Parity
       
*/
#define USART_PARITY   0 


/*
Options of USART_STOPBIT :

        0 => one stop bit
        1 => two stop bit
       
*/
#define USART_STOPBIT   1 


/* 
Options of USART_WORDSIZE :

        0 => 5-bit word size 
		1 => 6-bit word size
		2 => 7-bit word size
		3 => 8-bit word size
		4 => 9-bit word size
*/
#define  USART_WORDSIZE 3


#endif