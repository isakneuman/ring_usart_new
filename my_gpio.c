#include "my_gpio.h"

void pin_high(GPIO_TypeDef *GPIOx, uint8_t num){
	PIN_SET_BIT(GPIOx->BSRR,num);
}

void pin_low(GPIO_TypeDef *GPIOx, uint8_t num){
	GPIOx->BSRR = 1<<(num+16);
}

void gpio_port_clock(GPIO_TypeDef *GPIOx){
	if(!gpio_get_state(GPIOx)){
		switch( *((uint32_t*)(&GPIOx)) ){
			case GPIOA_BASE:
				RCC->APB2ENR |=  (1U << IOPAEN);
				break;
			case GPIOB_BASE:
				RCC->APB2ENR |=  (1U << IOPBEN);
				break;
			case GPIOC_BASE:
				RCC->APB2ENR |=  (1U << IOPCEN);
				break;
		}
	}
}

void init_i2c1_port(void){
	init_gpio(GPIOB,6,OUTPUT_ALLTER_OPEN_DRAIN,OUTPUT_MODE_50MHz);
	init_gpio(GPIOB,7,OUTPUT_ALLTER_OPEN_DRAIN,OUTPUT_MODE_50MHz);
}

void gpio_conf_set(GPIO_TypeDef *GPIOx, uint8_t num, uint8_t conf, uint8_t mode){
	volatile uint32_t *reg;
	
	if(num<8){
		reg = &GPIOx->CRL;
	}
	else{
		num -= 8;
		reg = &GPIOx->CRH;
	}
	*reg &= ~(0xF << ( num << 2));
	*reg |= ((conf << 2) | mode) << ( num << 2);
}

void init_gpio(GPIO_TypeDef *GPIOx, uint8_t num, uint8_t conf, uint8_t mode){
	gpio_port_clock(GPIOx);
	gpio_conf_set(GPIOx,num,conf,mode);
}

uint8_t gpio_get_state(GPIO_TypeDef *GPIOx){
	switch(*((uint32_t*)(&GPIOx))){
		case GPIOA_BASE:
			return (RCC->APB2ENR &  (1U << 2));
		case GPIOB_BASE:
			return (RCC->APB2ENR &  (1U << 3));
		case GPIOC_BASE:
			return (RCC->APB2ENR &  (1U << 4));
	}
	return 0;	
}
