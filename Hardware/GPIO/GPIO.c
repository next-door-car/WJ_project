#include "stm32f10x.h"                  // Device header

/*EN����*/
void EN_config()   						
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_5;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE); //���ҵ��
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);  //���ҵ��ʹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTUR);  //���µ��
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);  //���ҵ��ʹ��
}

void EN_First(uint8_t config)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,config);  //���ҵ��ʹ��
}

void EN_Second(uint8_t config)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,config);  //���ҵ��ʹ��
}

/*��һ�����MS����*/
void MS_First_config()
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

/*�ڶ������MS����*/
void MS_Second_config()
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

/*��ˮ���ú���*/
void Water(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_12;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTURE); 
}

/*�������ú���*/
void DIR_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE); //����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTUR;
	GPIO_Init_STRUCTUR.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTUR.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init_STRUCTUR.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTUR);  //����
} 

/*ȫ��MOTOR���ú���*/
void MS_config()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_SET); //MS1
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET); //MS2
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_15,Bit_SET); //MS1
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,Bit_SET); //MS2
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET); //����ˮ
}

/*���ҵ��������*/
void MOTOR_First_Dirct(uint8_t Dirct)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Dirct);  //��һ�������ת
}	

/*���µ��������*/
void MOTOR_Second_Dirct(uint8_t Dirct)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Dirct);  //��һ�������ת
}	

