#ifndef _MY_DELAY
	#define _MY_DELAY
	
	#include "global.h"
	
	extern volatile uint32_t ms;
	
	void init_my_delay(void);
	void SysTick_Handler(void);
	void delay_ms(uint32_t);
	
	
#endif
