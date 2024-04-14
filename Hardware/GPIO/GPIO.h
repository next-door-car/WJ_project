#ifndef _GPIO_H
#define _GPIO_H
#include <stdint.h>

/*注释

*/
#define Motor_First_Run Bit_SET //使能
#define Motor_First_DISRun Bit_RESET

#define Right 	Bit_SET
#define Left	Bit_RESET


#define Motor_Second_Run Bit_SET //使能
#define Motor_Second_DISRun Bit_RESET

void MOTOR_config(uint8_t motor_first_run ,uint8_t motor_second_run);
void MOTOR_First_Dirct(uint8_t Dirct);
void MOTOR_Second_Dirct(uint8_t Dirct);


#endif 
