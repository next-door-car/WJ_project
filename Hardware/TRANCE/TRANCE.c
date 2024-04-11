#include "stm32f10x.h"                  // Device header
#include "TRANCE.h"

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
	
	}
	else
	{
		/*不动*/
	
	}

}
static ENUM_FireContorl_STATE Model_Fire_First(void){

}
static ENUM_FireContorl_STATE Model_Fire_Second(void){

}