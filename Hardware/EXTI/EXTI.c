#include "stm32f10x.h"                  // Device header
#include "EXTI.h"
#include "UART.h"
uint8_t Left_Flag;                     // 左边限位PB13
uint8_t Right_Flag; 				   // 右边限位PB14
uint8_t Up_Flag;					   // 上边限位PB15
uint8_t Down_Flag;					   // 下边限位PA8

/*
PB13 左边限位
PB14 右边限位
PB15 上边限位
PA8  下边限位
*/
void EXTI_init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启AFIO的时钟，外部中断必须开启AFIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB13,PB14, PB15引脚初始化为上拉输入

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		                //将PA8引脚初始化为上拉输入

	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);//将外部中断的13号线映射到GPIOB，即选择PB13为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);//将外部中断的15号线映射到GPIOB，即选择PB15为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8); //将外部中断的8号线映射到GPIOA，即选择PA8为外部中断引脚
	
	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure;						//定义结构体变量
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;					//选择配置外部中断的13号线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//指定外部中断线为下降沿触发
	EXTI_Init(&EXTI_InitStructure);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;                 //选择配置外部中断的14号线
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line15;					//选择配置外部中断的15号线
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;					//选择配置外部中断的8号线
	EXTI_Init(&EXTI_InitStructure);

	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);				//配置NVIC为分组2
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		//选择配置NVIC的EXTI15_10线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		//选择配置NVIC的EXTI8线
	NVIC_Init(&NVIC_InitStructure);	

}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line13) == SET)		//判断是否是外部中断14号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
		{
			Left_Flag=1;	
		}
		EXTI_ClearITPendingBit(EXTI_Line13);		//清除外部中断13号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
	else if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			Right_Flag=1;	
		}
		EXTI_ClearITPendingBit(EXTI_Line14);		//清除外部中断14号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
	else if(EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)
		{
			Up_Flag=1;	
		}
		EXTI_ClearITPendingBit(EXTI_Line15);		//清除外部中断15号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}


}
    
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line8) == SET)		//判断是否是外部中断8号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
		{
			Down_Flag=1;	
		}
		EXTI_ClearITPendingBit(EXTI_Line8);		//清除外部中断8号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}
