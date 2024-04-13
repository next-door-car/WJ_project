#include "stm32f10x.h"                  // Device header
#include "GPIO.h"
#include "UART.h"
#include "Motor.h"
#include "PWM_Time.h"
#include "TRANCE.h"

int main(void)
{
	PWMFirst_config(80,72); 
	while(1){
        FireControl();
    }
	
}



