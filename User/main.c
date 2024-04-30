#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "Motor.h"
#include "PWM_Time.h"
#include "TRANCE.h"
#include "Delay.h"

void Text(int8_t arr , uint8_t DIr , int32_t step)
{
	MOTOR_First_Dirct(DIr);
	PWMFirst_config(arr, 72);
	Step_First=step;
	EN_First(EN);
}
int main(void)
{
	
	USART_init();
	DIR_config();
	MS_First_config();	
	MS_config(); 
	EN_config();  
	//Text(125, Right ,10000);
	
	
	//TIM_Cmd(TIM2,ENABLE);

	while(1){
	 FireControl();
    }
	
}



