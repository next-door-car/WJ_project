#include "stm32f10x.h"                  // Device header
#include "TRANCE.h"

uint16_t Step_First;  //左右电机脉冲总数
uint16_t Step_Second; //上下电机脉冲总数
uint32_t trance_x;     //左右电机坐标
uint32_t trance_y;	  //上下电机坐标
uint32_t Step_y;      //上下电机的总脉冲数
uint8_t i=1;            //上下电机的总脉冲数统计
int X_step;           //左右步数相关比例
int Y_step;			  //上下步数相关比例
uint8_t Dir=Right; //初始方向 顺时针

/* 灭火控制状态机:启动 */
ENUM_FireContorl_STATE FireModel = Fire_Start_Model; /* 控制状态机:是否启动 */
static ENUM_FireContorl_STATE Model_Fire_Reset(void);  /*开启复位校准*/
static ENUM_FireContorl_STATE Model_Fire_Start(void);  /*是否启动巡逻*/
static ENUM_FireContorl_STATE Model_Fire_First(void);  /*左右电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Second(void); /*上下电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Third(void);  /*喷水*/
static ENUM_FireContorl_STATE Model_Fire_Fourth(void);  /*第一电机继续运动，第二电机复位*/

/*状态机进行模式的选取*/
void FireControl(void)
{
	//static ENUM_FireContorl_STATE FireModel = Fire_Reset_Model;
	//ENUM_FireContorl_STATE FireModel = Fire_Third_Model;
	FireModel = Fire_Start_Model;
	switch (FireModel) 
	{
	case Fire_Reset_Model:  
         FireModel = Model_Fire_Reset(); //复位模式
		 	break;
	case Fire_Start_Model:
		 FireModel = Model_Fire_Start(); //开始模式 
			break;
    case Fire_First_Model:  
         FireModel = Model_Fire_First(); //第一步
			break;
	case Fire_Second_Model:  
         FireModel = Model_Fire_Second(); //第二步
			break;
	case Fire_Third_Model:  
         FireModel = Model_Fire_Third();  //第三步
			break;
	case Fire_Fourth_Model:  
         FireModel = Model_Fire_Fourth();  //第四步
			break;
	default:
			break;
	}
}


static ENUM_FireContorl_STATE Model_Fire_Reset(void)
{
	Motor_Reset_Around(400); //左右电机复位
	Motor_Reset_Bunk(400);   //上下电机复位
	FireModel = Fire_Start_Model;   //进入下一个模式
	return FireModel;
}


/*开始运动*/
ENUM_FireContorl_STATE Model_Fire_Start(void){
//	printf("first_mode\n");
//	printf("\n");
//	printf("\n");
//	printf(" AbB stop\n");
	PWMFirst_config(125,300); /*开始运动*/
	EN_First(EN);  //左右电机使能
	EN_Second(DISEN);//上下电机失能
	MOTOR_First_Dirct(Dir);  //顺时针
	TIM_Cmd(TIM2,ENABLE);	/*左右电机打开*/
	TIM_Cmd(TIM3,DISABLE);	/*上下电机关闭*/
	Fire_Start_Flag=0;    //标志位重置
	/*自由运动模式*/
	while(1)  /*火焰标志位*/
	{   
		if(Fire_Show_Flag==1)    //AbB
		{
			Fire_Show_Flag=0;
			TIM_Cmd(TIM2,DISABLE);
			break;
		}    //火焰出现，进入下一个状态
		else
		{
			if (Right_Flag == 1 || Left_Flag == 1)   // 达到右限位或左限位
			{
                Right_Flag=0;  
                Left_Flag=0;
				TIM_Cmd(TIM2,DISABLE);
				if(Dir==Bit_RESET)
				Dir=Bit_SET;
				else
				Dir=Bit_RESET;
				MOTOR_First_Dirct(Dir);
				TIM_Cmd(TIM2,ENABLE);	             
			}
				
		}	
	}
		Fire_Start_Flag=0;
		FireModel = Fire_First_Model;   //进入下一个模式
		printf("ok");
	
	
	return FireModel;
}


/*315<trance_x<325*/
/*235<trance_y<245*/
/*左右电机与上下电机无微调*/
static ENUM_FireContorl_STATE Model_Fire_First(void){   //左右电机校准
    
    PWMFirst_config(125,400); /*开始运动*/ 
//    printf("start\n ");
//    printf("trance_x=%d \n",trance_x);
//    printf("\n");
//    printf("TX0=%d \n",TX0);
//    printf("\n");
//    printf("TX1=%d \n",TX1);
//    int Dire;
	/*自由运动模式*/
    
	while(1)  /*火焰标志位*/
	{  
        if(trance_x<TX0)
        {
              Motor_StepLeft_Around(Right);    //向右走一步  
        }
        if(trance_x>=TX1)
        {
               Motor_StepRight_Around(Left);    //向左走一步   
        
        }
        if(trance_x<=TX1&&trance_x>=TX0)
              break;   
    }
    //FireModel = Fire_Second_Model;
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Second(void){  //上下电机校准
   
    PWMSecond_config(125*8,800); /*开始运动*/
	/*自由运动模式*/
	while(1)  /*火焰标志位*/
	{  
        if(trance_y<TY0)
        {
            Motor_StepUp_Bunk(UP);  //上下电机      
        }
        if(trance_y>=TY1)
        {
            Motor_StepDown_Bunk(DOWN);  //上下电机
        
        }
        if(trance_y<=TY1&&trance_y>=TY0)
            break;   
    }
    FireModel = Fire_Third_Model;
	return FireModel;
    
}

static ENUM_FireContorl_STATE Model_Fire_Third(void){
     
    PWMFirst_config(125,400); /*开始运动*/
     PWMSecond_config(125*8,800); /*开始运动*/
	printf("four_mode\n");
	printf("\n");
	printf("灭火标志AeB\n");
	TIM2_Flag=0;
	TIM3_Flag=0;
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET); //喷水
	Step_First=180;
	Step_Second=180;
	/*使用方形喷水*/ 
	while(1)              //喷水完成标志
	{
		MOTOR_First_Dirct(Right);				//方向
		MOTOR_Second_Dirct(UP);					//方向
		i=1;
		Step_y+=i*Step_Second;                  //计脉冲数
		
		EN_First(EN);//左右电机使能
		EN_Second(EN);//上下电机使能
		
		TIM_Cmd(TIM2,ENABLE); 					/*左右电机使能*/	
		TIM_Cmd(TIM3,ENABLE); 					/*上下电机使能*/
		while(1)
		{
			if(TIM2_Flag==1)
			{
				if(TIM3_Flag==1)
				{
				TIM2_Flag=0;
				TIM3_Flag=0;
				TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
				EN_First(DISEN);//左右电机失能
				TIM_Cmd(TIM3,DISABLE); /*关闭左右电机*/
				EN_Second(DISEN);//上下电机失能
				break;
				}
			}
			
		}                                        //第一轮微调完成
		if(Water_Flag==1)						 //接收到灭火完成标志
		{
			Water_Flag=0;
			GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET); //喷水关闭
			EN_First(DISEN);
			EN_Second(DISEN);
			TIM_Cmd(TIM2,DISABLE); 			/*左右电机失能*/
			TIM_Cmd(TIM3,DISABLE);			/*上下电机失能*/ 	
			FireModel = Fire_Fourth_Model; /*进入第四状态*/
			break;
		}
		Step_First=640;
		Step_Second=480;
		
		MOTOR_First_Dirct(Left);					//方向
		MOTOR_Second_Dirct(DOWN);					//方向
		i=-1;
		Step_y+=i*Step_Second;                  //计脉冲数
		
		EN_First(EN);//左右电机使能
		EN_Second(EN);//上下电机使能
		TIM_Cmd(TIM2,ENABLE); 					/*左右电机使能*/	
		TIM_Cmd(TIM3,ENABLE); 					/*上下电机使能*/
		
		while(1)
		{
			if(TIM2_Flag==1)
			{
				if(TIM3_Flag==1)
				{
				TIM2_Flag=0;
				TIM3_Flag=0;
				TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
				EN_First(DISEN);//左右电机失能
				TIM_Cmd(TIM3,DISABLE); /*关闭左右电机*/
				EN_Second(DISEN);//上下电机失能
				break;
				}
			}
			
		}											//第二轮微调完成
		if(Water_Flag==1)                             //接收到灭火完成标志AdB
		{
			Water_Flag=0;
			GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET); //喷水关闭
			EN_First(DISEN);
			EN_Second(DISEN);
			TIM_Cmd(TIM2,DISABLE); 			/*左右电机失能*/
			TIM_Cmd(TIM3,DISABLE);			/*上下电机失能*/ 
			FireModel = Fire_Fourth_Model; /*进入第四状态*/	
			break;
		}
		Step_First=640;
		Step_Second=480;
		
	}
	return FireModel;
}

ENUM_FireContorl_STATE Model_Fire_Fourth(void){
	
	Motor_Reset_Bunk(400);   //上下电机复位
	FireModel = Fire_Start_Model;	/*进入开始状态*/
	return FireModel;
}