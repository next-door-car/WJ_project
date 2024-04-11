#ifndef _DATA_H
#define _DATA_H
#include "stdint.h"



char usart_RxPacket[100];				//定义接收数据包数组
uint8_t USART_GetRxFlag(void);
uint16_t usart_RxFlag;					//定义接收数据包标志位

uint8_t Fire_Start_Flag = 0;            // 上位机控制左右电机







#endif 
