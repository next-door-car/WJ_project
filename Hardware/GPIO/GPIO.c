#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
/*EN配置*/
void EN_config()   						
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

/*第二个电机MS配置*/
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
void DIR_config()
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
void MS_config()
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

/*
PB13 左边限位
PB14 右边限位
PB15 上边限位
PA8  下边限位
*/

// void limit_init(void)
// {
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //开启GPIOA的时钟
// 	/*GPIO初始化*/
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB13,PB14, PB15引脚初始化为上拉输入

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);		                //将PA8引脚初始化为上拉输入
// }

/*
返回为1 即为正确
*/

// int limit_read(uint8_t limit)
// {
//     // 定义GPIO和引脚映射关系
//     const struct {
//         GPIO_TypeDef *GPIOx; // 修改为正确的指针类型
//         uint32_t GPIO_Pin;
//     } pin_map[] = {
//         {GPIOB, GPIO_Pin_13}, // Limit_Left
//         {GPIOB, GPIO_Pin_14}, // Limit_Right
//         {GPIOB, GPIO_Pin_15}, // Limit_UP
//         {GPIOA, GPIO_Pin_8},  // Limit_DOWN
//     };

//     // 检查limit值是否有效
//     if (limit < Limit_Left || limit > Limit_DOWN) {
//         // 返回错误码（这里假设错误码为-1）
//         return -1;
//     }

//     // 根据limit值获取对应的GPIO和引脚
//     GPIO_TypeDef *GPIOx = pin_map[limit - Limit_Left].GPIOx;
//     uint32_t GPIO_Pin = pin_map[limit - Limit_Left].GPIO_Pin;

//     // 读取GPIO引脚状态并返回结果
//     // 确保GPIO_ReadInputDataBit函数与修改后的类型匹配
//     return GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0 ? 1 : 0;
// }