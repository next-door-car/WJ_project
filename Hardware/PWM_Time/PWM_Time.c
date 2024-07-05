#include "stm32f10x.h"                  // Device header
#include "PWM_Time.h"

uint16_t First_i; //左右电机脉冲捕获计数
uint16_t Second_i; //左右电机脉冲捕获计数
uint16_t Limit_Around_Count; //左右限位复位计数
uint16_t Limit_Bunk_Count;	 //左右限位复位计数
uint8_t TIM2_Flag; //脉冲走完标志
uint8_t TIM3_Flag; //脉冲走完标志
uint32_t X_Allcount=1000; //从0-640 总需要的脉冲数  测试为1000
uint32_t Y_Allcount=1000; //从0-480 总需要的脉冲数	测试为1000

void PWMFirst_config(int16_t ARR_First, int16_t PSC_First)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InternalClockConfig(TIM2);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_STRUCTURE);
	//时基单元 
	TIM_TimeBaseInitTypeDef TIMSTRUCTURE;
	TIMSTRUCTURE.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMSTRUCTURE.TIM_CounterMode=TIM_CounterMode_Up;
	TIMSTRUCTURE.TIM_Period=ARR_First-1;//ARR
	TIMSTRUCTURE.TIM_Prescaler=PSC_First-1;//PSC
	TIMSTRUCTURE.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIMSTRUCTURE);	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIMstructure;
	TIM_OCStructInit(&TIMstructure);//负初始值
	TIMstructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIMstructure.TIM_OutputState=TIM_OutputState_Enable;
	TIMstructure.TIM_OutputNState =TIM_OutputNState_Enable;
	TIMstructure.TIM_Pulse=(ARR_First-1)/2;//设置ccr
	TIMstructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIMstructure.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIMstructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
	TIMstructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
	//PA1
	TIM_OC2Init(TIM2,&TIMstructure);
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 初始化NVIC寄存器
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);// 手动清除更新中断标志位，避免刚初始化完就近中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能更新中断TIM_Cmd
	TIM_Cmd(TIM2,DISABLE);
}

void PWMSecond_config(int16_t ARR_Second, int16_t PSC_Second)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Init_STRUCTURE;
	GPIO_Init_STRUCTURE.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init_STRUCTURE.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init_STRUCTURE.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_STRUCTURE);
	//时基单元 
	TIM_TimeBaseInitTypeDef TIMSTRUCTURE;
	TIMSTRUCTURE.TIM_ClockDivision=TIM_CKD_DIV1;
	TIMSTRUCTURE.TIM_CounterMode=TIM_CounterMode_Up;
	TIMSTRUCTURE.TIM_Period=ARR_Second-1;//ARR
	TIMSTRUCTURE.TIM_Prescaler=PSC_Second-1;//PSC
	TIMSTRUCTURE.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIMSTRUCTURE);	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIMstructure;
	TIM_OCStructInit(&TIMstructure);//负初始值
	TIMstructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIMstructure.TIM_OutputState=TIM_OutputState_Enable;
	TIMstructure.TIM_OutputNState =TIM_OutputNState_Enable;
	TIMstructure.TIM_Pulse=(ARR_Second-1)/2;//设置ccr
	TIMstructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIMstructure.TIM_OCNPolarity=TIM_OCNPolarity_High;
	TIMstructure.TIM_OCIdleState=TIM_OCIdleState_Reset;
	TIMstructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;
	//PA1
	TIM_OC3Init(TIM3,&TIMstructure);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); // 初始化NVIC寄存器
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);// 手动清除更新中断标志位，避免刚初始化完就近中断
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能更新中断TIM_Cmd
	TIM_Cmd(TIM3,DISABLE);
}


void TIM2_IRQHandler(void)
{ 	 
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //是更新中断
	{
		Limit_Around_Count++;
//		if(Limit_Around_Count>=80000)
//		Limit_Around_Count=0;
		if(First_i>=Step_First)
		{
			First_i=0;
			Step_First=0;
			TIM2_Flag=1;
		
		}
		else
			First_i++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除更新中断标志  
		
    }
}

void TIM3_IRQHandler(void)
{ 	 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		Limit_Bunk_Count++;
		if(Limit_Bunk_Count>=10000)
		Limit_Bunk_Count=0;
		if(Second_i>=Step_Second)
		{
			Second_i=0;
			Step_Second=0;
			TIM3_Flag=1; 
		
		}
		else
			Second_i++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除更新中断标志  
		
    }
}
