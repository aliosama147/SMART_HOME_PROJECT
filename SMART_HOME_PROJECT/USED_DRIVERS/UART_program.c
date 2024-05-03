#include "TYPES.h"
#include "BIT_MATH.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include "avr/interrupt.h"

#define F_CPU 8000000
#include "util/delay.h"

void (*CB_TX)(void);
void (*CB_RX)(void);
void (*CB_UDR)(void);

void USART_vidInit(u32 u8BaudRate)
{
	u16 Local_UBRR;
	/* Adjust Mode */
	CLR_BIT(USCRC,URSEL);
	#if    USART_MODE == 0

		CLR_BIT(USCRC,UMSEL);
		Local_UBRR = (8000000/(16*u8BaudRate))-1;
	#elif  USART_MODE == 2
		CLR_BIT(USCRC,UMSEL);
		SET_BIT(USCRA,U2X);
		Local_UBRR = (8000000/(8*u8BaudRate))-1;
	#else 
		SET_BIT(USCRC,UMSEL);
		Local_UBRR = (8000000/(2*u8BaudRate))-1;
	#endif
	
	/* Adjust Word Size */
	#if   USART_WORDSIZE == 0
		CLR_BIT(USCRC,UCSZ0);
		CLR_BIT(USCRC,UCSZ1);
		CLR_BIT(USCRB,UCSZ2);
	#elif USART_WORDSIZE == 1
		SET_BIT(USCRC,UCSZ0);
		CLR_BIT(USCRC,UCSZ1);
		CLR_BIT(USCRB,UCSZ2);
	#elif USART_WORDSIZE == 2
		CLR_BIT(USCRC,UCSZ0);
		SET_BIT(USCRC,UCSZ1);
		CLR_BIT(USCRB,UCSZ2);
	#elif USART_WORDSIZE == 3
		SET_BIT(USCRC,UCSZ0);
		SET_BIT(USCRC,UCSZ1);
		CLR_BIT(USCRB,UCSZ2);
	#else 
		SET_BIT(USCRC,UCSZ0);
		SET_BIT(USCRC,UCSZ1);
		SET_BIT(USCRB,UCSZ2);
	#endif
	
	/* Adjust Parity */
	#if   USART_PARITY  == 0
		CLR_BIT(USCRC,UPM0);
		CLR_BIT(USCRC,UPM1);
	#elif USART_PARITY  == 1
		CLR_BIT(USCRC,UPM0);
		SET_BIT(USCRC,UPM1);
	#else 
		SET_BIT(USCRC,UPM0);
		SET_BIT(USCRC,UPM1);
	#endif
	
	/* Adjust Stop bit */
	#if  USART_STOPBIT == 0
		CLR_BIT(USCRC,USBS);
	#else 
		SET_BIT(USCRC,USBS);
	#endif
	
	/* Enable TX and RX */
	SET_BIT(USCRB,TXEN);
	SET_BIT(USCRB,RXEN);
	
	/* Adjust UBRR */
	SET_BIT(USCRC,URSEL);
	UBRRH = (u8)(Local_UBRR >> 8);
	UBRRL = (u8)(Local_UBRR);
}
void USART_vidSendByte(u8 u8DataSend)
{
	while(GET_BIT(USCRA,UDRE)==0);
	UDR = u8DataSend ;
}

u8 USART_u8RecieveByte(void)
{
	while(GET_BIT(USCRA,RXC)==0);
	return UDR;
}

void USART_vidEnableTXInterrupt(void)
{
	SET_BIT(USCRB,TXCIE);
}

void USART_vidEnableRXInterrupt(void)
{
	SET_BIT(USCRB,RXCIE);
}

void USART_vidEnableUDREInterrupt(void)
{
	SET_BIT(USCRB,UDRIE);
}

void USART_vidSetCBTX(void(*CB)(void))
{
	CB_TX = CB;
}

void USART_vidSetCBRX(void(*CB)(void))
{
	CB_RX = CB;
}

void USART_vidSetCBUDRE(void(*CB)(void))
{
	CB_UDR = CB;
}

void USART_vidSendString(u8 *ptrString)
{
	while((*ptrString) != '\0')
	{
		USART_vidSendByte(*ptrString);
		ptrString++;
	}
}

void USART_vidSendu32Block(u32 u32DataSend)
{
	u8 Data;
	u8 counter;
	for(counter = 0; counter <=3 ; counter ++)
	{
		Data = (u8)(u32DataSend >> (8*counter));
		USART_vidSendByte(Data);
	}
}
u32 USART_u32Recieveu32Block(void)
{
	u32 Data;
	u8 counter;
	for(counter = 0; counter <=3 ; counter ++)
	{
		Data |=(USART_u8RecieveByte() << (8* counter)); 
	} 
	return Data;
}