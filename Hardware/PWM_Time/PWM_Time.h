#ifndef _PWM_Time_H
#define _PWM_Time_H

#include <stdint.h>



extern uint16_t i;
extern uint16_t counts;
extern uint16_t flag;

void PWM_init(uint8_t ARR, uint8_t PSC);


#endif 
