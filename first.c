#include "first.h"

void magic_function(void){
	//	r_data_position
	//	0		1		2		
	//	x		x		
	uint8_t a				=	0;
	uint8_t result	= 0;
	uint8_t TXEIE_	=	0;
	uint8_t buff[SUM_element];
	
	a = get_r_position();
	
	if(a>=1){
		read_r_data(buff,SUM_element);
		result = (uint8_t)sum_of_array(buff,SUM_element);
		write_t_data(&result,SUM_element-1);
		set_r_count(0);
		set_r_position(0);
		
		set_t_position(0);
		set_t_count(1);
		
		/*for(uint8_t i = 0, j = 0; i <= count; i=i+2){
			set_t_position(j);
			t_data[j++]	=	(uint16_t)sum_of_array((r_data+i),SUM_element);
			t_data_count		=	j;
		}
		if(r_data_count%2!=0){
			r_data[0]	=	r_data[r_data_position];	
			r_data_position	=	0;
			r_data_count		=	1;
		}
		else{
			r_data_position	=	r_data_count	=	0;
		}*/
		//
		set_flag_TXE(TRUE);
		USART1->CR1		|=	USART_CR1_TXEIE;
		TXEIE_	=	(USART1->CR1 & USART_CR1_TXEIE);
	}
}
