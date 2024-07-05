#include "stm32f10x.h"                  // Device header
#include "Motor.h"


void Motor_Reset_Around(uint16_t CCR)
{
        uint16_t Around_Sum;
        PWMFirst_config(125,CCR); /*开始运动*/
		MOTOR_First_Dirct(Right);  //顺时针
        EN_First(EN);  //左右电机使能
		TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
        //printf("start\r\n");
        while (1)
        {
            if(Left_Flag == 1)     //左限位
            {
                Left_Flag=0;
                EN_First(DISEN);
                TIM_Cmd(TIM2,DISABLE); 
                Limit_Around_Count=0;
                break;
            }
        }
        MOTOR_First_Dirct(Left);  //逆时针
        EN_First(EN);  //左右电机使能
        TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
        while(1)
        {
             if( Right_Flag== 1)     //右限位
            {
                Right_Flag=0;
                EN_First(DISEN);
                TIM_Cmd(TIM2,DISABLE);
                printf("%d\n",Limit_Around_Count);         //查看总脉冲数
                Around_Sum=Limit_Around_Count/2;          //要走脉冲数
                Limit_Around_Count=0;
                break;
            }
        }
        Step_First = Around_Sum;
        MOTOR_First_Dirct(Right);  //顺时针
        EN_First(EN);        //使能
        TIM_Cmd(TIM2,ENABLE); /*上下电机*/
        TIM2_Flag=0;  //标志清零
        while(1)
        {
            if(TIM2_Flag==1)
            {
                TIM2_Flag=0;
                EN_First(DISEN);//上下电机失能
                TIM_Cmd(TIM2,DISABLE); /*关闭上下电机*/
                break;
            }
        }
}//左右电机从中心到限位Around_Sum

void Motor_Reset_Bunk(uint16_t CCR)
{
        uint16_t Bunk_Sum; 
        PWMSecond_config(125*8,CCR); /*开始运动*/
		MOTOR_Second_Dirct(UP);  //向上
        EN_Second(EN);  //上下电机使能
		TIM_Cmd(TIM3,ENABLE);	/*上下电机打开*/
        while (1)
        {
            if(Up_Flag == 1)     //上限位
            {
                Up_Flag=0;
                EN_Second(DISEN);
                TIM_Cmd(TIM3,DISABLE);
                Limit_Bunk_Count=0;
                break;
            }
        }
        MOTOR_Second_Dirct(DOWN);  //向下
        EN_Second(EN);  //上下电机使能
        TIM_Cmd(TIM3,ENABLE);	/*上下电机打开*/
        while(1)
        {
             if(Down_Flag == 1)     //下限位
            {
                Down_Flag=0;
                EN_Second(DISEN);
                TIM_Cmd(TIM3,DISABLE);
                printf("%d\n",Limit_Bunk_Count);         //查看总脉冲数
                Bunk_Sum=Limit_Bunk_Count/2;          //要走脉冲数
                Limit_Bunk_Count=0;
                break;
            }
        }
        Step_Second = Bunk_Sum;
        MOTOR_Second_Dirct(UP);  //向上
        EN_Second(EN);        //使能
        TIM_Cmd(TIM3,ENABLE); /*上下电机*/
        TIM3_Flag=0;  //标志清零
        while(1)
        {
            if(TIM3_Flag==1)
            {
                TIM3_Flag=0;
                EN_Second(DISEN);//上下电机失能
                TIM_Cmd(TIM3,DISABLE); /*关闭上下电机*/
                break;
            }
        }
}//上下电机从中心到限位Bunk_Sum