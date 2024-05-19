#ifndef _Motor_H
#define _Motor_H
#include "GPIO.h"
#include "PWM_Time.h"
#include "UART.h"

extern uint8_t TIM2_Flag;   //定时器2走完脉冲标志
extern uint8_t TIM3_Flag;   //定时器3走完脉冲标志
extern uint16_t Limit_Around_Count;  //左右限位复位计数
extern uint16_t Limit_Bunk_Count;	 //左右限位复位计数


void Motor_Reset_Around(void);  //左右电机复位
void Motor_Reset_Bunk(void);    //上下电机复位
#endif 
