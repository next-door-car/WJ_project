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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructur;
	GPIO_InitStructur.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructur.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructur.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructur);
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_RESET);
    
    GPIO_InitTypeDef GPIO_InitStructu;
	GPIO_InitStructu.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructu.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructu.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructu);
    GPIO_WriteBit(GPIOA,GPIO_Pin_6,Bit_SET);
}
void open(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
}
void close(void)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
}

void Text_UART()
{
		if(Fire_Start_Flag==1)  //AaB
		{
			Fire_Start_Flag=0;
			open();
			while(1)
			{
				if(Fire_Show_Flag==1) //AbB
				{
					Fire_Show_Flag=0;
					close();
					break;
				}
			}
		}

}

void Text_v1(int8_t arr , uint8_t DIr)  //motor first
{
	MOTOR_First_Dirct(DIr);
	PWMFirst_config(arr, 400);
	EN_First(EN);
	TIM_Cmd(TIM2,ENABLE);
}
void Text_v2(int16_t arr , int16_t DIr)  //motor second
{
	MOTOR_Second_Dirct(DIr);
	PWMSecond_config(arr, 400);
	EN_Second(EN);
	TIM_Cmd(TIM3,ENABLE);
}
void Text_motor_dir()
{
		MOTOR_First_Dirct(Right);  //顺时针
		Step_First = 3000;
		EN_First(EN);//左右电机失能
		TIM_Cmd(TIM2,ENABLE); /*关闭左右电机*/
		while(1)
		{
		if(TIM2_Flag==1)
			{
			TIM2_Flag=0;
			EN_First(DISEN);//左右电机失能
			TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
			break;
			}
		}
		MOTOR_First_Dirct(Left);  //顺时针
		Step_First = 3000;
		EN_First(EN);//左右电机失能
		TIM_Cmd(TIM2,ENABLE); /*关闭左右电机*/
		while(1)
		{
		if(TIM2_Flag==1)
			{
			TIM2_Flag=0;
			EN_First(DISEN);//左右电机失能
			TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
			break;
			}
		}
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
	Water();
	PWMFirst_config(125,400); /*开始运动*/ 
    
	//Text_v1(125, Right);  //motor first

	//Text_v2(125 , UP);  //motor second
	while(1){
        
	FireControl();

        
    }
	
}



