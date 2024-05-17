#ifndef _PWM_Time_H
#define _PWM_Time_H

#include <stdint.h>



extern uint16_t Step_First;
extern uint16_t Step_Second;
void PWMFirst_config(int16_t ARR_First, int16_t PSC_First);
void PWMSecond_config(int16_t ARR_Second, int16_t PSC_Second);


#endif 
