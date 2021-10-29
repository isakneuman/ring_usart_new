#include "button.h"

volatile uint8_t button_state1=0;
volatile uint8_t button_state2=0;

void check_button1(GPIO_TypeDef *GPIOx, uint8_t num){
	static uint32_t button_count;
	if( GPIOx->IDR & (1<<num) ){
		button_count++;
	}
	else{
			if( button_count>SHORT_DURATION ){
				button_count = 0;
				button_state1 = 1;
			}
			else{
				button_count = 0;
				button_state1 = 0;
			}
	}
}

void check_button2(GPIO_TypeDef *GPIOx, uint8_t num){
	static uint32_t button_count;
	if( GPIOx->IDR & (1<<num) ){
		button_count++;
	}
	else{
			if( button_count>SHORT_DURATION ){
				button_count = 0;
				button_state2 = 1;
			}
			else{
				button_count = 0;
				button_state2 = 0;
			}
	}
}

void init_button(GPIO_TypeDef *GPIOx, uint8_t num){
	
	init_gpio(GPIOx,num,INPUT_UpDown,INPUT_MODE);
	GPIOx->ODR &= ~(1<<num);
	
}
