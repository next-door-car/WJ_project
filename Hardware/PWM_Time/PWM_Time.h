#ifndef _PWM_Time_H
#define _PWM_Time_H

#include <stdint.h>



extern uint16_t Step_First;
extern uint16_t Step_Second;
void PWMFirst_config(int8_t ARR_First, int8_t PSC_First);
void PWMSecond_config(int8_t ARR_Second, int8_t PSC_Second);


#endif 
