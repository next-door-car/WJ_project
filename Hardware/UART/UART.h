#include <stdio.h>
#include "stdint.h"
#ifndef _UART_H
#define _UART_H


extern uint32_t trance_x;
extern uint32_t trance_y;


void USART_init(void);
void USART_SendByte(uint16_t Byte);
void USART_SendString(char *String);
void USART_SendArray(uint16_t *Array, uint16_t Length);
void Uart_DATA(void);




#endif 

