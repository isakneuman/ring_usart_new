#ifndef _MY_GPIO
	#define _MY_GPIO
	
	#include "global.h"
	
	#define PIN_SET_BIT(x,y)	x |= (1<<y)
	
	#define IOPAEN										2
	#define IOPBEN										3
	#define IOPCEN										4
	
	#define INPUT_MODE								0x00
	#define OUTPUT_MODE_10MHz					0x01
	#define OUTPUT_MODE_2MHz					0x02
	#define OUTPUT_MODE_50MHz					0x03
	
	#define INPUT_ANALOG							0x00
	#define INPUT_FLOAT								0x01
	#define INPUT_UpDown							0x02
	#define INPUT_Reverved						0x11
	
	#define OUTPUT_PUSH_PULL					0x00 // 00
	#define OUTPUT_OPEN_DRAIN					0x01 // 01
	#define OUTPUT_ALLTER_PUSH_PULL 	0x02 // 10
	#define OUTPUT_ALLTER_OPEN_DRAIN	0x03 // 11
	
	void pin_high(GPIO_TypeDef *GPIOx, uint8_t num);
	void pin_low(GPIO_TypeDef *GPIOx, uint8_t num);
	
	void gpio_conf_set(GPIO_TypeDef *GPIOx, uint8_t num, uint8_t conf, uint8_t mode);
	void gpio_port_clock(GPIO_TypeDef*);
	void init_gpio(GPIO_TypeDef *GPIOx, uint8_t num, uint8_t conf, uint8_t mode);
	void init_i2c1_port(void);
	uint8_t gpio_get_state(GPIO_TypeDef*);
		
#endif
