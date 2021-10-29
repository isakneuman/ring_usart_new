#include "init_usart.h"

void USART1_IRQHandler(void);


static 		uint8_t		r_data[RBUFF_SIZE];
static		uint8_t 	r_data_count			=	0;
static		uint8_t 	r_data_position		=	0;

static 		uint8_t		t_data[TBUFF_SIZE];
static		uint8_t 	t_data_count			=	0;
static		uint8_t 	t_data_position		=	0;

uint8_t set_flag_TXE(uint8_t i){
	return (flag_TXE	=		 i);
}
uint8_t get_flag_TXE(void){
	return flag_TXE;
}

uint8_t get_r_count(void){
	return r_data_count;
}
uint8_t get_t_count(void){
	return t_data_count;
}
uint8_t get_r_position(void){
	return r_data_position;
}
uint8_t get_t_position(void){
	return t_data_position;
}
// end get

void set_r_count(uint8_t i){
	r_data_count	=	i;
}
void set_t_count(uint8_t i){
	t_data_count	=	i;
}	
void set_r_position(uint8_t i){
	r_data_position	=	i;
}
void set_t_position(uint8_t i){
	t_data_position	=	i;
}
// end set

uint8_t read_r_data(uint8_t* buff,uint8_t count){
	uint8_t i = 0;
	for(i=0; i<count; i++){
		*(buff+i)	=	*(r_data+i); 
	}
	return i;
}
uint8_t write_t_data(uint8_t* buff,uint8_t count){
	uint8_t i = 0;
	for(i=0; i<count; i++){
		*(t_data+i) = *(buff+i); 
	}
	return i;
}

void USART1_IRQHandler(void){
	
	if ( USART1->SR & USART_SR_RXNE ){
		if(r_data_count == RBUFF_SIZE){
			r_data_count	=	0;
		}
		
		r_data_position		=	r_data_count;
		r_data[r_data_count]	=	USART1->DR;
		r_data_count++;
	}
	if ( (USART1->SR & USART_SR_TXE) && get_flag_TXE()){
		USART1->DR	=	t_data[t_data_position++];
		if(t_data_position == t_data_count){
			set_flag_TXE(FALSE);
			USART1->CR1			&=	~USART_CR1_TXEIE;
			t_data_position	=		t_data_count	=	0;
		}
	}
}
//	END USART1_IRQHandler



uint16_t BRR(uint16_t BAUDR){
	uint16_t DIV_Mantissa			=	( (SystemCoreClock/BAUDR/16)	<<4 );
	uint16_t DIV_Fraction			=	( ((SystemCoreClock/BAUDR)%16)*16	);
	return ( (uint16_t)(DIV_Mantissa|DIV_Fraction) );
}
//	END BRR

void init_usart(uint16_t brr){

	RCC->APB2ENR	|= 	RCC_APB2ENR_USART1EN;
	USART1->BRR		= 	BRR(brr);
	USART1->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ (USART1_IRQn);
	init_gpio(GPIOA,TX_pin,OUTPUT_ALLTER_PUSH_PULL,OUTPUT_MODE_10MHz);
	init_gpio(GPIOA,RX_pin,INPUT_FLOAT,INPUT_MODE);
	
}
//	END init_usart


