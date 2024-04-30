#ifndef _GPIO_H
#define _GPIO_H
#include <stdint.h>

/*注释

*/

#define EN 			Bit_RESET
#define DISEN 		Bit_SET

#define Right 	Bit_SET
#define Left	Bit_RESET
#define UP 		Bit_SET
#define DOWN	Bit_RESET

#define Motor_Second_Run Bit_SET //使能
#define Motor_Second_DISRun Bit_RESET

void DIR_config();
void MOTOR_First_Dirct(uint8_t Dirct);
void MOTOR_Second_Dirct(uint8_t Dirct);
void EN_config();   	
void EN_Second(uint8_t config);
void EN_First(uint8_t config);
void MS_config();
void MS_First_config();
void MS_Second_config();
void Water();


#endif 
