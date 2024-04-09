#ifndef _UART_H
#define _UART_H

void USART_init(void);
void USART_SendByte(uint8_t Byte);
void USART_SendString(char *String);
uint8_t USART_GetRxFlag(void);
uint8_t USART_GetRxData(void);
void USART1_IRQHandler(void);


#endif 

