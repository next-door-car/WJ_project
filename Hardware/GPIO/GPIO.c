#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
/*EN配置*/
void EN_config(void)   						
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE); //左右电机
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);  //左右电机使能
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTUR);  //上下电机
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);  //左右电机使能
}

void EN_First(uint8_t config)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,config);  //左右电机使能
}

void EN_Second(uint8_t config)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,config);  //左右电机使能
}

/*第一个电机MS配置*/
void MS_First_config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTURE); //MS1
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Init_STRUCTUR);  //MS2
}  

/*第二个电机MS配置*/
void MS_Second_config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE); //MS1
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTUR);  //	MS2
} 

/*喷水配置函数*/
void Water(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTURE); 
}

/*方向配置函数*/
void DIR_config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE); //左右
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTUR);  //上下
} 

/*全局MOTOR配置函数*/
void MS_config(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_SET); //MS1
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET); //MS2
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_15,Bit_SET); //MS1
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET); //MS2
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET); //不喷水
}

/*左右电机方向函数*/
void MOTOR_First_Dirct(uint8_t Dirct)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Dirct);  //第一个电机右转
}	

/*上下电机方向函数*/
void MOTOR_Second_Dirct(uint8_t Dirct)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Dirct);  //第一个电机右转
}	

