#ifndef _TRANCE_H
#define _TRANCE_H
#include <stdint.h>
#include "GPIO.h"
#include "UART.h"
#include "PWM_Time.h"
typedef enum
{
	//左边环岛枚举阶段（-1）
	Fire_Start_Model = 1,   /*上位机控制是否启动 */
	Fire_First_Model,       /*左右电机运动到指定位置 */
	Fire_Second_Model,      /*上下电机运动到指定位置*/
    Fire_Third_Model,       /*进行喷水*/
    Fire_Fourth_Model,      /*复位状态*/

} ENUM_FireContorl_STATE;

extern uint8_t Fire_Start_Flag;  /*上位机控制下位机运动*/
extern uint8_t Fire_Show_Flag;   /*火焰出现标志*/
extern ENUM_FireContorl_STATE FireModel;


#define YMIN 10
#define XMIN 10
#define COL 640
#define ROW 480
#define TX0 ((COL-50)/2) // 315
#define TX1 ((COL+50)/2) // 325
#define TY0 ((ROW-50)/2) // 235
#define TY1 ((ROW+50)/2) // 245

void FireControl(void);

#endif 
