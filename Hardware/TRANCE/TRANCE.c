#include "stm32f10x.h"                  // Device header
#include "TRANCE.h"

void FireControl(void)
{
  static g_FireState = E_FireInit;
	switch (g_FireState) 
	{
	case E_FireInit:
		 g_FireState = FireInit(); 
			break;
	case E_FireCAimd:  
			break;
	case E_FireSwin:
			break; 
	case E_FireStop:
			break;
	default:
			break;
	}
}