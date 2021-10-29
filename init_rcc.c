#include "init_rcc.h"

uint8_t init_HSE_PLL(void){
	RCC->CR |= RCC_CR_HSEON;
	
	__IO uint16_t start_up_counter;
	
	for(start_up_counter=0; ;start_up_counter++){
		if(start_up_counter>0x1000){
			RCC->CR &= ~RCC_CR_HSEON;
			return 0;
		}
		if(RCC->CR & RCC_CR_HSERDY){
			return 1;
		}
	}
	
	RCC->CFGR |= RCC_CFGR_PLLMULL9 | RCC_CFGR_PLLSRC;
}
