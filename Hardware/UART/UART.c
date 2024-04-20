#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "UART.h"


char usart_RxPacket[100];				//定义接收数据包数组
uint8_t USART_GetRxFlag(void);
uint16_t usart_RxFlag;					//定义接收数据包标志位

uint8_t Fire_Start_Flag = 0;            // 上位机控制左右电机
uint8_t Fire_Show_Flag = 0;             /*火焰出现标志*/
uint8_t Water_Flag = 0;             	/*喷水完成标志*/

uint8_t DATA_Flag = 0;       			/*接收坐标标志*/
static uint8_t Data_Length = 0; 		//接收数据长度

/*加入对printf的支持*/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


/**
  * 函    数：串口初始化
  * 参    数：无
  * 返 回 值：无
  */
void USART_init(void){
		/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//开启USART1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA9引脚初始化为复用推挽输出
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA10引脚初始化为上拉输入
	
	/*USART初始化*/
	USART_InitTypeDef USART_InitStructure;					//定义结构体变量
	USART_InitStructure.USART_BaudRate = 9600;				//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制，不需要
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//模式，发送模式和接收模式均选择
	USART_InitStructure.USART_Parity = USART_Parity_No;		//奇偶校验，不需要
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位，选择1位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//字长，选择8位
	USART_Init(USART1, &USART_InitStructure);				//将结构体变量交给USART_Init，配置USART1
	
	/*中断输出配置*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//开启串口接收数据的中断
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//配置NVIC为分组2
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;					//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//选择配置NVIC的USART1线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);							//将结构体变量交给NVIC_Init，配置NVIC外设
	
	/*USART使能*/
	USART_Cmd(USART1, ENABLE);								//使能USART1，串口开始运行
}

/**
  * 函    数：串口发送一个字节
  * 参    数：Byte 要发送的一个字节
  * 返 回 值：无
  */
void USART_SendByte(uint16_t Byte)
{
	USART_SendData(USART1, Byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完成
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}
/**
  * 函    数：串口发送一个数组
  * 参    数：Array 要发送数组的首地址
  * 参    数：Length 要发送数组的长度
  * 返 回 值：无
  */
void USART_SendArray(uint16_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)		//遍历数组
	{
		USART_SendByte(Array[i]);		//依次调用Serial_SendByte发送每个字节数据
	}
}

/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void USART_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)    //遍历字符数组（字符串），遇到字符串结束标志位后停止
	{
		USART_SendByte(String[i]);		//依次调用Serial_SendByte发送每个字节数据
	}
}

/**
  * 函    数：获取串口接收标志位
  * 参    数：无
  * 返 回 值：串口接收标志位，范围：0~1，接收到数据后，标志位置1，读取后标志位自动清零
  */
uint8_t USART_GetRxFlag(void)
{
	if (usart_RxFlag == 1)			//如果标志位为1
	{
		usart_RxFlag = 0;
		return 1;					//则返回1，并自动清零标志位
	}
	return 0;						//如果标志位为0，则返回0
}

/**
  * 函    数：USART1中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void USART1_IRQHandler(void)
{
	
	static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
	static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
    uint16_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
				/*使用状态机的思路，依次处理数据包的不同部分*/
		
		/*当前状态为0，接收数据包包头*/
		if (RxState == 0)
		{
			if (RxData == 'A')			//如果数据确实是包头
			{
				 
				RxState = 1;			//置下一个状态
				pRxPacket = 0;			//数据包的位置归零
				Data_Length=1;			//数据长度为1
			}
		}
		
		/*当前状态为1，接收数据包数据*/
		else if (RxState == 1)
		{
			
			if(RxData == 'a')
			{
				Fire_Start_Flag = 1;    /*上位机控制左右电机*/
				RxState = 2;
			}
			else if(RxData == 'b')
			{
			
				Fire_Show_Flag = 1;    /*火焰出现标志*/
				RxState = 2;
			}
			else if(RxData == 'c')
			{
			
				Water_Flag = 1;   		 /*火焰消灭标志*/
				RxState = 2;
			}
			else
			{
			usart_RxPacket[pRxPacket] = RxData;	//将数据存入数据包数组的指定位置
			pRxPacket ++;				//数据包的位置自增
			}
			Data_Length++;              //长度自增
			if(Data_Length==10)
				RxState = 2;
		}
		
		/*当前状态为2，接收数据包包尾*/
		else if (RxState == 2)
		{
			if (RxData == 'B')			//如果数据确实是包尾部
			{	
				if(Data_Length==3)
					printf("正确接收");
				else
				{
					printf("接收坐标");
					Uart_DATA();
				}
					
				RxState = 0;			//状态归0
				usart_RxPacket[pRxPacket] = '\0';
				usart_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
			}
		}
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			//清除USART1的RXNE标志位
                                                                //读取数据寄存器会自动清除此标志位
	                                                            //如果已经读取了数据寄存器，也可以不执行此代码
	}
}

void Uart_DATA(void){
	trance_x = 0; trance_y = 0;
	u16 len = Data_Length & 0x3fff; //得到此次接收到的数据长度(注意不包含末尾的 A 与 B )
	trance_x = ((usart_RxPacket[0] - '0')*1000)+((usart_RxPacket[1] - '0')*100)+((usart_RxPacket[2] - '0')*10)+(usart_RxPacket[3] - '0');
    trance_y = ((usart_RxPacket[5] - '0')*1000)+((usart_RxPacket[6] - '0')*100)+((usart_RxPacket[7] - '0')*10)+(usart_RxPacket[8] - '0');
	printf("%d %d",trance_x,trance_y);  //测试trance_x ,trance_y
}
  
