#ifndef _MCAL_UART_INTERFACE_H_
#define _MCAL_UART_INTERFACE_H_
#include "TYPES.h"

void USART_vidInit(u32 u8BaudRate);

void USART_vidSendByte(u8 u8DataSend);

u8 USART_u8RecieveByte(void);

void USART_vidEnableTXInterrupt(void);

void USART_vidEnableRXInterrupt(void);

void USART_vidEnableUDREInterrupt(void);

void USART_vidSetCBTX(void(*CB)(void));

void USART_vidSetCBRX(void(*CB)(void));

void USART_vidSetCBUDRE(void(*CB)(void));

void USART_vidSendString(u8 *ptrString);

void USART_vidSendu32Block(u32 u32DataSend);

u32 USART_u32Recieveu32Block(void);
#endif