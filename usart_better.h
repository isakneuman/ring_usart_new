#ifndef _RING_USART
#define _RING_USART

	#include "global.h"
	
	#define TX_PIN		9
	#define RX_PIN		10
	#define TRUE			1
	#define FALSE			0
	#define BUFF_SIZE	16
	#define END_OWN_WORD	7
	#define	ENTER_value	'b'
	extern 	uint8_t 	flag_TXE;
	extern 	uint8_t		flag_RXNE;
	
	extern 	uint8_t 	tbuff[BUFF_SIZE];
	extern 	uint8_t 	rbuff[BUFF_SIZE];
	extern	uint8_t		count_r;
	extern	uint8_t		tail_r;
	extern	uint8_t		head_r;
	extern	uint8_t 	count_t;
	extern	uint8_t		tail_t;
	extern	uint8_t		head_t;
	extern	uint8_t		counter_OWN_word;

	void		transfer(void);
	void		check_for_send(void);
	
	uint8_t		get_count_r(void);
	uint8_t		get_count_t(void);
	
	uint8_t		get_counter_OWN_word(void);
	void			set_counter_OWN_word(uint8_t);
	
	uint8_t		get_tail_t(void);
	uint8_t		get_tail_r(void);
	uint8_t		get_head_t(void);
	uint8_t		get_head_r(void);
	void			set_tail_t(uint8_t);
	void			set_tail_r(uint8_t);
	void			set_head_t(uint8_t);
	void			set_head_r(uint8_t);
	
	void			init_my_word(void);
	void 			create_send_buff(void);
	void 			check_in_range(uint8_t*);
	
	// TXE flag
	uint8_t set_flag_TXE(uint8_t i);
	uint8_t get_flag_TXE(void);
	
	// RXNE flag
	uint8_t set_flag_RXNE(uint8_t i);
	uint8_t get_flag_RXNE(void);
	
	// BAUDRATE
	uint16_t BRR(uint16_t);
	
	// INIT
	void 	init_usart(uint16_t brr);
	
	// USART IRQHandler
	void USART1_IRQHandler(void);
#endif