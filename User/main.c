#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "Motor.h"
#include "PWM_Time.h"
#include "TRANCE.h"
#include "Delay.h"


int main(void)
{
	
	USART_init();
	PWMFirst_config(80,72); 
	PWMSecond_config(80,72); 
	MOTOR_First_Dirct(Right);
	MOTOR_Second_Dirct(UP);
	MOTOR_config(Motor_First_Run ,Motor_Second_Run); /*���ô����ҵ��*/
	
	/*�߶���������λ*/
	Step_First=10000;
	Step_Second=10000;
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
//	MOTOR_config(Motor_First_DISRun,Motor_Second_DISRun);  //����
	while(1){
//        FireControl();
    }
	
}



