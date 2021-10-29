#include "init_timer.h"

void init_tim1(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
}