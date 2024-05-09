#ifndef _TRANCE_H
#define _TRANCE_H
#include <stdint.h>
#include "GPIO.h"
#include "UART.h"
#include "PWM_Time.h"
#include "Delay.h"
typedef enum
{
	//左边环岛枚举阶段（-1）
	Fire_Start_Model = 1,   /*上位机控制是否启动 */
	Fire_First_Model,       /*左右电机运动到指定位置 */
	Fire_Second_Model,      /*上下电机运动到指定位置*/
    Fire_Third_Model,       /*进行喷水*/
    Fire_Fourth_Model,      /*复位状态*/

} ENUM_FireContorl_STATE;

extern uint8_t Fire_Start_Flag;   /*上位机控制下位机运动 AaB*/
extern uint8_t Fire_Show_Flag;    /*火焰出现标志 AbB*/
extern uint8_t MOTOR_Around_Flag; /*左右电机校准标志 AcB*/
extern uint8_t MOTOR_Updown_Flag; /*上下电机校准标志 AdB*/
extern uint8_t Water_Flag;		  /*火焰消灭标志*/
extern uint8_t Dir_Flag;    	  /*左右电机限位标志*/
extern uint32_t X_Allcount; //从0-640 总需要的脉冲数
extern uint32_t Y_Allcount; //从0-480 总需要的脉冲数
extern uint8_t TIM2_Flag;   //定时器2走完脉冲标志
extern uint8_t TIM3_Flag;   //定时器3走完脉冲标志
extern ENUM_FireContorl_STATE FireModel;

#define YMIN 10
#define XMIN 10
#define COL 640
#define ROW 480
#define TX ((COL)/2) // 315
#define TY ((ROW)/2) // 315
#define TX0 ((COL-50)/2) // 315
#define TX1 ((COL+50)/2) // 325
#define TY0 ((ROW-50)/2) // 235
#define TY1 ((ROW+50)/2) // 245


void FireControl(void);

#endif 
