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
uint8_t Dir=Bit_RESET; //初始方向 顺时针

/* 灭火控制状态机:启动 */
ENUM_FireContorl_STATE FireModel = Fire_Start_Model; /* 控制状态机:是否启动 */
static ENUM_FireContorl_STATE Model_Fire_Start(void);  /*是否启动巡逻*/
static ENUM_FireContorl_STATE Model_Fire_Reset(void);  /*开启复位校准*/
static ENUM_FireContorl_STATE Model_Fire_First(void);  /*左右电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Second(void); /*上下电机启动校准*/
static ENUM_FireContorl_STATE Model_Fire_Third(void);  /*喷水*/
static ENUM_FireContorl_STATE Model_Fire_Fourth(void);  /*第一电机继续运动，第二电机复位*/

/*状态机进行模式的选取*/
void FireControl(void)
{
	static ENUM_FireContorl_STATE FireModel = Fire_Start_Model;
	//FireModel = Fire_Second_Model;
	switch (FireModel) 
	{
	case Fire_Start_Model:
		 FireModel = Model_Fire_Start();  
			break;
	case Fire_Reset_Model:  
         FireModel = Model_Fire_Reset();
		 	break;
    case Fire_First_Model:  
         FireModel = Model_Fire_First(); 
			break;
	case Fire_Second_Model:  
         FireModel = Model_Fire_Second(); 
			break;
	case Fire_Third_Model:  
         FireModel = Model_Fire_Third(); 
			break;
	case Fire_Fourth_Model:  
         FireModel = Model_Fire_Fourth(); 
			break;
	default:
			break;
	}
}

/*串口发送AaB 开始运动*/
ENUM_FireContorl_STATE Model_Fire_Start(void){

	if(Fire_Start_Flag == 1)     //AaB
	{
		printf("first_mode\n");
		printf("\n");
		printf("\n");
		printf(" AbB stop\n");
		PWMFirst_config(125,400); /*开始运动*/
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
		    // else
			// {
			// 	if (limit_read(Limit_Left) == 0 || limit_read(Limit_Right) == 0)    //达到限位
			// 	{
			// 			TIM_Cmd(TIM2,DISABLE);
			// 			if(Dir==Bit_RESET)
			// 			Dir=Bit_SET;
			// 			else
			// 			Dir=Bit_RESET;
			// 			MOTOR_First_Dirct(Dir);
			// 			TIM_Cmd(TIM2,ENABLE);			
			// 	}
				
			// }	
		}
		Fire_Start_Flag=0;
		FireModel = Fire_First_Model;   //进入下一个模式
		//FireModel = Fire_Second_Model;
		
	}
	else
	{
		/*不动*/
		EN_First(DISEN);//左右电机失能
		EN_Second(DISEN);//上下电机失能
		TIM_Cmd(TIM2,DISABLE); /*左右电机*/
		TIM_Cmd(TIM3,DISABLE);	/*上下电机*/
	
	}
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Reset(void)
{
	Motor_Reset_Around(); //左右电机复位
	Motor_Reset_Bunk();   //上下电机复位
	FireModel = Fire_First_Model;   //进入下一个模式
	return FireModel;
}

/*315<trance_x<325*/
/*235<trance_y<245*/
/*左右电机与上下电机无微调*/
static ENUM_FireContorl_STATE Model_Fire_First(void){   //左右电机校准

	printf("second_mode\r\n");
	printf("\n");
	/*需要先发送坐标，再发送校准标志
	如：
	A1000 2000B
	AcB
	*/
	printf("sent coordinate\r\n");   /*发送坐标*/
	printf("\n");
	printf(" AcB\r\n");
	printf("\n");
	MOTOR_Around_Flag=0;
	while(1)
	{
		if(MOTOR_Around_Flag==1) 
		{
			MOTOR_Around_Flag=0;
			break;
		}
	}
	printf("\n");
	printf("coordinate received\r\n");  /*接收坐标*/
	
	
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
	Step_First=X_step;                          //左右脉冲数
	//************************************************//
	/*
	uint32_t a,b,c;
	a=trance_x-TX;
	b=a*X_Allcount;
	c=b/TX;
	printf("\n");
	printf("%d\r\n",TX);
	printf("%d\r\n",trance_x);
	printf("%d\r\n",a);
	printf("%d\r\n",b);
	printf("%d\r\n",c); 
	*/
	//************************************************//

	EN_First(EN);//左右电机失能
	TIM_Cmd(TIM2,ENABLE); /*关闭左右电机*/
	TIM2_Flag=0;   //标志清零
	while(1)
	{
		if(TIM2_Flag==1)
		{
			TIM2_Flag=0;
			EN_First(DISEN);//左右电机失能
			TIM_Cmd(TIM2,DISABLE); /*关闭左右电机*/
			break;
		}
	}
		
	FireModel = Fire_Second_Model;	/*进入第二状态*/
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Second(void){  //上下电机校准
	
	printf("three_mode\r\n");
	printf("\n");
	printf(" AdB\r\n");
	printf("\n");
	//****************************************//
	/*发送校准标志
	如果需要校准坐标
	需要先发送坐标
	AdB
	*/
	PWMSecond_config(125*8,400); 			    //初始化 频率差了8倍 
	while(1)
	{
		if(MOTOR_Updown_Flag==1)
		{
			MOTOR_Updown_Flag=0;
			break;
		}
	}
	printf("\n");
	printf(" AdB\n");
	printf("coordinate received\r\n");
	//****************************************//
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
	//***************************************************//
	/*
	uint32_t a,b,c;
	a=trance_y-TY;
	b=a*Y_Allcount;
	c=b/TY;
	printf("\n");
	printf("%d\r\n",TY);
	printf("%d\r\n",trance_y);
	printf("%d\r\n",a);
	printf("%d\r\n",b);
	printf("%d\r\n",c); 
	*/
	//***************************************************//
	Step_Second=Y_step;
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
	FireModel = Fire_Third_Model; /*进入第三状态*/
	return FireModel;
}

static ENUM_FireContorl_STATE Model_Fire_Third(void){
	//*************************************************
	// PWMFirst_config(125,400);
	// PWMSecond_config(125,400);
	//************************************************
	printf("four_mode\n");
	printf("\n");
	printf("灭火标志AeB\n");
	TIM2_Flag=0;
	TIM3_Flag=0;
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET); //喷水
	Step_First=320;
	Step_Second=240;
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
			//FireModel = Fire_Fourth_Model; /*进入第四状态*/
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
			break;
		}
		Step_First=640;
		Step_Second=480;
		
	}
	FireModel = Fire_Fourth_Model; /*进入第四状态*/
	return FireModel;
}

ENUM_FireContorl_STATE Model_Fire_Fourth(void){
	printf("five_mode\n");
	EN_First(EN);	
	TIM_Cmd(TIM2,ENABLE); 			/*左右电机使能*/	
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
	EN_Second(EN);							//上下电机使能
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