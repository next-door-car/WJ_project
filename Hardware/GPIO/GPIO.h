#ifndef _GPIO_H
#define _GPIO_H
#include <stdint.h>

/*注释

*/
#define Motor_First_Run Bit_SET //使能
#define Motor_First_DISRun Bit_RESET
#define Motor_First_Right Bit_SET //右转
#define Motor_First_Left Bit_RESET //左转

#define Motor_Second_Run Bit_SET //使能
#define Motor_Second_DISRun Bit_RESET
#define Motor_Second_Right Bit_SET //上转
#define Motor_Second_Left Bit_RESET //下转

void MOTOR_config(uint8_t motor_first_run ,uint8_t motor_first_dirt,
		uint8_t motor_second_run,uint8_t motor_second_dirt);


#endif 
