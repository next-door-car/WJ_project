#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "EXTI.h"
#include "Motor.h"
#include "PWM_Time.h"
#include "TRANCE.h"
#include "Delay.h"


void GPIO_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void open(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
}
void close(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
}



void Text(int8_t arr , uint8_t DIr , int32_t step)
{
	MOTOR_First_Dirct(DIr);
	PWMFirst_config(arr, 72);
	Step_First=step;
	EN_First(EN);
}
int main(void)
{
	delay_init();
	USART_init();
	EXTI_init();
	GPIO_init();
	DIR_config();
	MS_First_config();	
	MS_Second_config();	
	MS_config(); 
	EN_config();  
//	Text(125, Right ,10000);
//	TIM_Cmd(TIM2,ENABLE);

	while(1){
//		if(Dir_Flag==1)
//		{
//			Dir_Flag=0;
//		    open();
//			printf("nihaonihao\r\n");	
//		}
	  FireControl();
    }
	
}



