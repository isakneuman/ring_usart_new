#ifndef _BUTTON
#define _BUTTON
	#include "global.h"

	#define SHORT_DURATION 		20
	#define LONG_DURATION_LOW	1000
	#define LONG_DURATION_HIGH	3000

	extern volatile uint8_t button_state1;
	extern volatile uint8_t button_state2;

	void check_button1(GPIO_TypeDef *GPIOx, uint8_t num);
	void check_button2(GPIO_TypeDef *GPIOx, uint8_t num);
	
	
	void init_button(GPIO_TypeDef *GPIOx, uint8_t num);

#endif
