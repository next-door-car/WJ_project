#ifndef _UART_H
#define _UART_H

#include <stdio.h>

extern char usart_RxPacket[];				//定义接收数据包数组

void USART_init(void);
void USART_SendByte(uint16_t Byte);
void USART_SendString(char *String);
void USART_SendArray(uint16_t *Array, uint16_t Length);

uint8_t USART_GetRxFlag(void);


#endif 

