#include "my_delay.h"

volatile uint32_t ms = 0;

void init_my_delay(void){
	SysTick_Config( (SystemCoreClock/1000)-1 );
}

void delay_ms(uint32_t n){
	uint32_t current = ms;
	while((ms-current)<n);
}

void SysTick_Handler(void){
	ms++;
	check_button1(GPIOA,5);
	check_button2(GPIOA,6);
}

