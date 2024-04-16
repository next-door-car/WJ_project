#include "stm32f10x.h"                  // Device header
#include "TRANCE.h"

uint16_t Step_First;  //左右电机脉冲总数
uint16_t Step_Second; //上下电机脉冲总数
uint8_t trance_x;     //左右电机坐标
uint8_t trance_y;	  //上下电机坐标
uint32_t Step_y;      //上下电机的总脉冲数
uint8_t i=1;            //上下电机的总脉冲数统计
int X_step;           //左右步数相关比例
int Y_step;			  //上下步数相关比例


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
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);  //左右电机使能
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//上下电机失能
		TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
		TIM_Cmd(TIM3,DISABLE);	/*上下电机关闭*/
		
		/*自由运动模式*/
		while(!Fire_Show_Flag)  /*火焰标志位*/
		{   
			MOTOR_First_Dirct(Right);
			MOTOR_config(Motor_First_Run ,Motor_Second_DISRun); /*配置打开左右电机*/
			
			/*走多少碰到限位*/
			
			
			
		}
		FireModel = Fire_First_Model;
	}
	else
	{
		/*不动*/
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);//左右电机失能
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//上下电机失能
		TIM_Cmd(TIM2,DISABLE); /*左右电机*/
		TIM_Cmd(TIM3,DISABLE);	/*上下电机*/
	
	}
	return FireModel;
}

/*315<trance_x<325*/
/*235<trance_y<245*/
/*左右电机与上下电机无微调*/
static ENUM_FireContorl_STATE Model_Fire_First(void){   //左右电机校准
	TIM_Cmd(TIM2,DISABLE); /*左右电机*/
	if(TX > trance_x)
	{
		MOTOR_First_Dirct(Left);                //方向
		X_step = (TX-trance_x)*X_Allcount/TX;   //需要的脉冲总数
	}
	else
	{
		MOTOR_First_Dirct(Right);				//方向
		X_step = (trance_x-TX)*X_Allcount/TX;
	
	}
	Step_First=X_step;
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);//左右电机使能
	TIM_Cmd(TIM2,ENABLE); /*左右电机*/
	if(TIM2_Flag==1)
	{
		TIM2_Flag=0;
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);//左右电机失能
		TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
	}
	FireModel = Fire_Second_Model;	/*进入第二状态*/
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Second(void){  //上下电机校准
	if(TY > trance_y)
	{
		MOTOR_Second_Dirct(DOWN);                //方向
		Y_step = (TY-trance_y)*Y_Allcount/TY;   //需要的脉冲总数
		i=-1;
	}
	else
	{
		MOTOR_Second_Dirct(UP);					//方向
		Y_step = (trance_y-TY)*Y_Allcount/TY;
		i=1;
	
	}
	Step_y=i*Y_step;                            //以向上为正需要的脉冲总数
	Step_Second=Y_step;
	TIM_Cmd(TIM3,ENABLE); /*上下电机*/
	if(TIM3_Flag==1)
	{
		TIM3_Flag=0;
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//上下电机失能
		TIM_Cmd(TIM3,DISABLE); /*关闭上下电机*/
	}
	
	FireModel = Fire_Third_Model; /*进入第三状态*/
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Third(void){
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET); //喷水
	/*使用方形喷水*/ 
	while(1)              //喷水完成标志
	{
		Step_First=100;
		Step_Second=100;
		
		MOTOR_First_Dirct(Right);				//方向
		MOTOR_Second_Dirct(UP);					//方向
		i=1;
		Step_y+=i*Step_Second;                  //计脉冲数
		
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);//左右电机使能
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//上下电机使能
		
		TIM_Cmd(TIM2,ENABLE); 					/*左右电机使能*/	
		TIM_Cmd(TIM3,ENABLE); 					/*上下电机使能*/
		while(TIM2_Flag==1&&TIM3_Flag==1)
		{
			TIM2_Flag=0;
			TIM3_Flag=0;
			TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
			GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);//左右电机失能
			TIM_Cmd(TIM3,DISABLE); /*关闭左右电机*/
			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//上下电机失能
		}
		if(Water_Flag==1)						 //接收到灭火完成标志
		{
			Water_Flag=0;
			break;
		
		}
		Step_First=200;
		Step_Second=200;
		
		MOTOR_First_Dirct(Left);					//方向
		MOTOR_Second_Dirct(DOWN);					//方向
		i=-1;
		Step_y+=i*Step_Second;                  //计脉冲数
		
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);//左右电机使能
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//上下电机使能
		TIM_Cmd(TIM2,ENABLE); 					/*左右电机使能*/	
		TIM_Cmd(TIM3,ENABLE); 					/*上下电机使能*/
		
		while(TIM2_Flag==1&&TIM3_Flag==1)
		{
			TIM2_Flag=0;
			TIM3_Flag=0;
			TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
			GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);//左右电机失能
			TIM_Cmd(TIM3,DISABLE); /*关闭上下电机*/
			GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);//上下电机失能
		}
		if(Water_Flag==1)                             //接收到灭火完成标志
		{
			Water_Flag=0;
			break;
		}
		
	}
	
	FireModel = Fire_Fourth_Model; /*进入第四状态*/
}

ENUM_FireContorl_STATE Model_Fire_Fourth(void){
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET); //喷水关闭
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);//左右电机使能
	TIM_Cmd(TIM2,ENABLE); 					/*左右电机使能*/	
	if(Step_y>0)					/*向下运动*/
	{
		MOTOR_Second_Dirct(DOWN);
	}
	else
	{
		Step_y=-1*Step_y;
		MOTOR_Second_Dirct(UP);
	
	}
	Step_Second=Step_y;
	GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);//上下电机使能
	TIM_Cmd(TIM3,ENABLE); 					/*上下电机使能*/
	while(1)
	{
		if(TIM3_Flag==1)
		{
			TIM3_Flag=0;
			break;
		}
			
	}
	
	FireModel = Fire_Start_Model;	/*进入开始状态*/
	return FireModel;
}