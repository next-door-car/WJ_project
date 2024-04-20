#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "PWM_Time.h"
#include "Delay.h"

uint16_t i=0;
uint16_t flag=0;
uint16_t counts;

uint16_t arr=90;
uint16_t ccr=72;
void setup(void){
	
 delay_init();  
 USART_init();
 PWM_init(arr,72); //TIM2 DISABLE
 gpio_config();    //EN引脚使能 
 TIM_Cmd(TIM2,DISABLE);
	
}
void pwm(void){
	arr=120;
	TIM_Cmd(TIM2,DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	PWM_init(arr,72); //TIM2 DISABLE
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	TIM_Cmd(TIM2,ENABLE);
	delay_us(300);
	arr=110;
	TIM_Cmd(TIM2,DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	PWM_init(arr,72); //TIM2 DISABLE
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	TIM_Cmd(TIM2,ENABLE);
	delay_us(300);
	arr=100;
	TIM_Cmd(TIM2,DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	PWM_init(arr,72); //TIM2 DISABLE
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	TIM_Cmd(TIM2,ENABLE);
	delay_us(300);
	arr=90;
	TIM_Cmd(TIM2,DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	PWM_init(arr,72); //TIM2 DISABLE
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
	TIM_Cmd(TIM2,ENABLE);
//	delay_ms(1);
//	arr=100;
//	TIM_Cmd(TIM2,DISABLE);
//	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
//	PWM_init(arr,72); //TIM2 DISABLE
//	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
//	TIM_Cmd(TIM2,ENABLE);
//	delay_ms(1);
//	arr=110;
//	TIM_Cmd(TIM2,DISABLE);
//	GPIO_SetBits(GPIOA, GPIO_Pin_8);  //使能引脚
//	PWM_init(arr,72); //TIM2 DISABLE
//	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //使能引脚
//	TIM_Cmd(TIM2,ENABLE);
//	delay_ms(1);
}
int main(void)
{
	
	 setup();
	
	//TIM_Cmd(TIM2,ENABLE);
	pwm();
	
	

	  while(1)
	  {
		  
		 
	  }
 
}
	
