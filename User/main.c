#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "DATA.h"
#include "Motor.h"
#include "PWM_Time.h"
#include "oled.h"


int main(void)
{
	USART_init();
  USART_SendByte(0x0041);	
	
	while(1)
	{

		
			
		if(USART_GetRxFlag() == 1)
		{
     USART_SendString(usart_RxPacket);
		}
			
	}
}

