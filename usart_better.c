#include "usart_better.h"


uint8_t 	tbuff[BUFF_SIZE];
uint8_t 	rbuff[BUFF_SIZE];

uint8_t		count_t	=	0;
uint8_t		tail_t	=	END_OWN_WORD;
uint8_t		head_t	=	END_OWN_WORD;
uint8_t 	count_r	=	0;
uint8_t		tail_r	=	0;
uint8_t		head_r	=	0;

uint8_t		counter_OWN_word	=	0;

uint8_t 	read_from_tbuff(void);
void 			write_in_tbuff(uint8_t);

uint8_t 	read_from_rbuff(void);
void			write_in_rbuff(uint8_t	data);

uint8_t 	flag_TXE	=	0;
uint8_t		flag_RXNE	=	0;

uint8_t		get_counter_OWN_word(void){
	return	counter_OWN_word;
}
void			set_counter_OWN_word(uint8_t value){
	counter_OWN_word	=	value;
}

uint8_t		get_count_t(void){
	if( get_tail_t() <= get_head_t() ){
		return ( get_head_t()-get_tail_t() );
	}
	else{
		return (BUFF_SIZE-get_tail_t()+get_head_t());
	}
}
uint8_t		get_count_r(void){
	if( get_tail_r() <= get_head_r() ){
		return ( get_head_r()-get_tail_r() );
	}
	else{
		return (BUFF_SIZE-get_tail_r()+get_head_r());
	}
}

uint8_t 	set_flag_TXE(uint8_t i){
	return (flag_TXE	=		 i);
}
uint8_t 	get_flag_TXE(void){
	return flag_TXE;
}

uint8_t 	set_flag_RXNE(uint8_t i){
	return (flag_RXNE	=		 i);
}
uint8_t 	get_flag_RXNE(void){
	return flag_RXNE;
}
//
uint8_t	get_tail_t(void){
	return	tail_t;
}
uint8_t	get_tail_r(void){
	return	tail_r;
}
uint8_t	get_head_t(void){
	return	head_t;
}
uint8_t	get_head_r(void){
	return	head_r;
}
void			set_tail_t(uint8_t value){
	tail_t	=	value;
}
void			set_tail_r(uint8_t value){
	tail_r	=	value;
}
void			set_head_t(uint8_t value){
	head_t	=	value;
}
void			set_head_r(uint8_t value){
	head_r	=	value;
}
//

void			init_my_word(void){
	tbuff[0]	=	'H';
	tbuff[1]	=	'e';
	tbuff[2]	=	'l';
	tbuff[3]	=	'l';
	tbuff[4]	=	'o';
	tbuff[5]	=	',';
	tbuff[6]	=	' ';
}

void 			create_send_buff(void){
	uint8_t new_element_count	=	get_count_r();
	for(uint8_t i = 0; i < new_element_count; i++){
		write_in_tbuff( *(rbuff+get_tail_r()) );
		set_tail_r( get_tail_r()+1 );
		if( get_tail_r()>=BUFF_SIZE ){
		 set_tail_r(0);
		}
	}
}

void 			write_in_tbuff(uint8_t	data){
	*(tbuff+get_head_t())	=	data;
	set_head_t(get_head_t()+1);
	if(get_head_t()>=BUFF_SIZE){
		set_head_t(END_OWN_WORD);
	}
}
// end write_in_tbuff

void			transfer(void){
	if(get_counter_OWN_word()<END_OWN_WORD){
		USART1->DR	=	*(tbuff+get_counter_OWN_word());
		set_counter_OWN_word(get_counter_OWN_word()+1);
	}
	else{
		uint8_t new_element_count	=	get_count_t();
		USART1->DR	=	*(tbuff+get_tail_t());
		set_tail_t(get_tail_t()+1);
		if(get_tail_t()>=BUFF_SIZE){
			set_tail_t(END_OWN_WORD);
		}
		if( new_element_count == 1 ){
			//get_tail_t() == get_head_t()
			set_counter_OWN_word(0);
			set_flag_TXE(FALSE);
			USART1->CR1			&=	~USART_CR1_TXEIE;
		}
	}
}
// end transfer

void			check_for_send(void){
	uint8_t temvalue = get_head_r();
	if(temvalue	==	0){
		temvalue	=	BUFF_SIZE;
	}
	if(*(rbuff+(temvalue-1)) == ENTER_value ){
		set_head_r(get_head_r()-1);
		set_flag_TXE(TRUE);
		USART1->CR1		|=	USART_CR1_TXEIE;
	}
}
// end check_for_send

void			write_in_rbuff(uint8_t	data){
	*(rbuff+get_head_r()) = data;
	set_head_r(get_head_r()+1);
	if(get_head_r()>=BUFF_SIZE){
			set_head_r(0);
	}
}

void 			USART1_IRQHandler(void){
	if ( USART1->SR & USART_SR_RXNE ){
		write_in_rbuff(USART1->DR);
	}
	if ( (USART1->SR & USART_SR_TXE) && get_flag_TXE()){
		transfer();
	}
}
//	END IRQHandler

uint16_t 	BRR(uint16_t BAUDR){
	
	uint16_t DIV_Mantissa			=	( (SystemCoreClock/BAUDR/16)	<<	4 );
	uint16_t DIV_Fraction			=	( ((SystemCoreClock/BAUDR)%16)*16	);
	return ( (uint16_t)(DIV_Mantissa|DIV_Fraction) );
}
//	END BRR

void 			init_usart(uint16_t brr){

	RCC->APB2ENR	|= 	RCC_APB2ENR_USART1EN;
	USART1->BRR		= 	BRR(brr);
	USART1->CR1  	|= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ (USART1_IRQn);
	init_gpio(GPIOA,TX_PIN,OUTPUT_ALLTER_PUSH_PULL,OUTPUT_MODE_10MHz);
	init_gpio(GPIOA,RX_PIN,INPUT_FLOAT,INPUT_MODE);
}
//	END INIT