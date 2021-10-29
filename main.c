#include "global.h"

int main(){
	
	SystemInit();
	
	// led init
	init_gpio(GPIOB,0,OUTPUT_PUSH_PULL,OUTPUT_MODE_10MHz);
	init_gpio(GPIOA,7,OUTPUT_PUSH_PULL,OUTPUT_MODE_10MHz);
	
	// button init
	init_button(GPIOA,5);
	init_button(GPIOA,6);
	
	// delay iniy
	init_my_delay();
	
	// usart init
	init_usart(9600);
	init_my_word();
	
	while(1){
		// button test
		check_for_send();
		create_send_buff();
		
		
		if(button_state1){
			GPIOA->ODR ^= GPIO_ODR_ODR7;
			button_state1 = 0;
		}
		if(button_state2){
			GPIOB->ODR ^= GPIO_ODR_ODR0;
			button_state2 = 0;
		}
		
	}
}

