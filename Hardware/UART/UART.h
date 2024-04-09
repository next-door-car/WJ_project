#ifndef _UART_H
#define _UART_H

#include <stdio.h>

extern char usart_RxPacket[];				//定义接收数据包数组
extern uint32_t data1;       //x坐标
extern uint32_t data2;       //y坐标
	
void USART_init(void);
uint32_t USART_Pow(uint32_t X, uint32_t Y);
void USART_SendNumber(uint32_t Number, uint8_t Length);
void USART_SendByte(uint16_t Byte);
void USART_SendString(char *String);
void USART_SendArray(uint16_t *Array, uint16_t Length);

uint8_t USART_GetRxFlag(void);


#endif 

