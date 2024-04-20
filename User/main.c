#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "PWM_Time.h"
#include "Delay.h"


uint16_t i=0;
uint16_t flag=0;
uint16_t counts;

uint16_t arr=80;
uint16_t ccr=72;
void setup(void){
	
 delay_init();  
 USART_init();
 PWM_init(arr,ccr); //TIM2 DISABLE
 gpio_config();    //EN引脚使能 
 TIM_Cmd(TIM2,ENABLE);
}
void Motor(uint8_t count,uint32_t num)
{
	for(i=0;i<count;i++){
	counts=num;
	TIM_CtrlPWMOutputs(TIM2, ENABLE);     //输出PWM
	while(!flag);
	if(flag==1)	
	{
		flag=0;
		delay_ms(2);
	}
		
	}
	


}
int main(void)
{

	 setup();
	 Motor(1,3000);

	  while(1);
 
}
	
