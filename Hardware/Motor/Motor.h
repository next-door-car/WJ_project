#ifndef _Motor_H
#define _Motor_H
#include "GPIO.h"
#include "PWM_Time.h"
#include "UART.h"

extern uint8_t TIM2_Flag;   //定时器2走完脉冲标志
extern uint8_t TIM3_Flag;   //定时器3走完脉冲标志
extern uint16_t Limit_Around_Count;  //左右限位复位计数
extern uint16_t Limit_Bunk_Count;	 //左右限位复位计数
extern uint8_t Left_Flag;    	  /*左电机限位标志*/
extern uint8_t Right_Flag;    	  /*右电机限位标志*/
extern uint8_t Up_Flag;    	  	  /*上电机限位标志*/
extern uint8_t Down_Flag;    	  /*下电机限位标志*/


void Motor_Reset_Around(uint16_t CCR);  //左右电机复位
void Motor_Reset_Bunk(uint16_t CCR);    //上下电机复位
void Motor_StepLeft_Around(int Dir);    //左一步
void Motor_StepRight_Around(int Dir);   //右一步
void Motor_StepUp_Bunk(int Dir);        //上一步
void Motor_StepDown_Bunk(int Dir);      //下一步

void Around_StepLeft_Start(int Dir);
void Around_StepRight_Start(int Dir);
void Bunk_StepUp_Start(int Dir);
void Bunk_StepDown_Start(int Dir);
    

#endif 
