#include "stm32f10x.h"                  // Device header
#include "Motor.h"


void Motor_Reset_Around(void)
{
    GPIO_init();
        uint16_t Around_Sum;
        // PWMFirst_config(200,72); /*开始运动*/
		// MOTOR_First_Dirct(Right);  //顺时针
        // EN_First(EN);  //左右电机使能
		// TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
        printf("start\r\n");
        while (1)
        {
            if(limit_read(Limit_Right) == 1)     //右限位
            {
                open();
                // printf("1\r\n");
                // EN_First(DISEN);
                // TIM_Cmd(TIM2,DISABLE);
                // Limit_Around_Count=0;
                // break;
            }
        }
        MOTOR_First_Dirct(Left);  //逆时针
        EN_First(EN);  //左右电机使能
        TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
        while(1)
        {
             if(limit_read(Limit_Left) == 1)     //左限位
            {
                EN_First(DISEN);
                TIM_Cmd(TIM2,DISABLE);
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
}

void Motor_Reset_Bunk(void)
{
        uint16_t Bunk_Sum; 
        PWMSecond_config(125,72); /*开始运动*/
		MOTOR_Second_Dirct(UP);  //向上
        EN_Second(EN);  //上下电机使能
		TIM_Cmd(TIM3,ENABLE);	/*上下电机打开*/
        while (1)
        {
            if(limit_read(Limit_UP) == 1)     //上限位
            {
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
             if(limit_read(Limit_DOWN) == 1)     //下限位
            {
                EN_Second(DISEN);
                TIM_Cmd(TIM3,DISABLE);
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
}