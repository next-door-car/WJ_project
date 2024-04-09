#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "DATA.h"
#include "Motor.h"
#include "PWM_Time.h"

     
uint8_t RxData;			//定义用于接收串口数据的变量

int main(void)
{
	
	USART_init();
	
	while(1)
		{
			if (USART_GetRxFlag() == 1)			//检查串口接收数据的标志位
		{
			RxData = USART_GetRxData();		//获取串口接收的数据
			USART_SendByte(RxData);			//串口将收到的数据回传回去，用于测试
		}
	}
}

