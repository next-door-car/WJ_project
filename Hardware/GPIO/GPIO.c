#include "stm32f10x.h"                  // Device header

void gpio_config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);  //Ê¹ÄÜÒý½Å
}