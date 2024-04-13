#ifndef _PWM_Time_H
#define _PWM_Time_H

#include <stdint.h>



extern uint16_t Step_First;
extern uint16_t Step_Second;
void PWMFirst_config(uint8_t ARR_First, uint8_t PSC_First);
void PWMSecond_config(uint8_t ARR_Second, uint8_t PSC_Second);


#endif 
