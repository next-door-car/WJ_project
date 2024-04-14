#include "stm32f10x.h"                  // Device header
#include "TRANCE.h"

uint16_t Step_First;  //左右电机脉冲总数
uint16_t Step_Second; //上下电机脉冲总数
uint8_t trance_x;     //左右电机坐标
uint8_t trance_y;	  //上下电机坐标
/* 灭火控制状态机:启动 */
ENUM_FireContorl_STATE FireModel = Fire_Start_Model; /* 控制状态机:是否启动 */
static ENUM_FireContorl_STATE Model_Fire_Start(void);  /*是否启动巡逻*/
static ENUM_FireContorl_STATE Model_Fire_First(void);  /*左右电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Second(void); /*上下电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Third(void);  /*喷水*/
static ENUM_FireContorl_STATE Model_Fire_Fourth(void);  /*第一电机继续运动，第二电机复位*/

/*状态机进行模式的选取*/
void FireControl(void)
{
//  static FireModel = Fire_Start_Model;
	switch (FireModel) 
	{
	case Fire_Start_Model:
		 FireModel = Model_Fire_Start();  
			break;

    case Fire_First_Model:  
         FireModel = Model_Fire_First(); 

	case Fire_Second_Model:  
         FireModel = Model_Fire_Second(); 
			break;
	default:
			break;
	}
}

ENUM_FireContorl_STATE Model_Fire_Start(void){
	if(Fire_Start_Flag == 1)
	{
		/*开始运动*/
		TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
		TIM_Cmd(TIM3,DISABLE);	/*上下电机关闭*/
		
		/*自由运动模式*/
		while(!Fire_Show_Flag)  /*火焰标志位*/
		{   
			MOTOR_First_Dirct(Right);
			MOTOR_Second_Dirct(Right);
			MOTOR_config(Motor_First_Run ,Motor_Second_DISRun); /*配置打开左右电机*/
			
			/*走多少碰到限位*/
			
			
			
		}
		FireModel = Fire_First_Model;
	}
	else
	{
		/*不动*/
		TIM_Cmd(TIM2,DISABLE); /*左右电机*/
		TIM_Cmd(TIM3,DISABLE);	/*上下电机*/
	
	}
	return FireModel;
}
static ENUM_FireContorl_STATE Model_Fire_First(void){   //左右电机校准
	

	return FireModel;
}
static ENUM_FireContorl_STATE Model_Fire_Second(void){  //上下电机校准

	return FireModel;
}
